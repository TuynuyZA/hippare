//-------------------------------------------------------------------
//背景の表示
//-------------------------------------------------------------------
#include  "MyPG.h"
#include  "Task_player.h"
#include "Task_Title.h"

namespace  Player
{
  Resource::WP  Resource::instance;
  //-------------------------------------------------------------------
  //リソースの初期化
  bool  Resource::Initialize()
  {
	return true;
  }
  //-------------------------------------------------------------------
  //リソースの解放
  bool  Resource::Finalize()
  {
    return true;
  }
  //-------------------------------------------------------------------
  //「初期化」タスク生成時に１回だけ行う処理
  bool  Object::Initialize()
  {
	  //スーパークラス初期化
	  __super::Initialize(defGroupName, defName, true);
	  //リソースクラス生成orリソース共有
	  this->res = Resource::Create();

	  //★データ初期化
	  this->imageName = "Ball";
	  DG::Image_Create(this->imageName, "./data/image/Ball.png");

	  //this->controllerName = "P1";
	  //this->pos.x = (1028 - 128)/2;
	  //this->pos.y = 680;

	  return true;

	  //★タスクの生成

	  return true;
  }
  //-------------------------------------------------------------------
  //「終了」タスク消滅時に１回だけ行う処理
  bool  Object::Finalize()
  {
    //★データ＆タスク解放
    if (!ge->QuitFlag() && this->nextTaskCreate) {
      //★引き継ぎタスクの生成
      Title::Object::Create(true);
    }

    return  true;
  

  }
  //-------------------------------------------------------------------
  //「更新」１フレーム毎に行う処理
  void  Object::UpDate()
  {
    auto in = DI::GPad_GetState("P1");
	if (in.LStick.L.on) { pos.x -= 5; }
	if (in.LStick.R.on) { pos.x += 5; }
	if (in.LStick.U.on) { pos.y -= 5; }
	if (in.LStick.D.on) { pos.y += 5; }
  }
  //-------------------------------------------------------------------
  //「２Ｄ描画」１フレーム毎に行う処理
  void  Object::Render2D_AF()
  {
    //  状態管理配列を上にかぶせカードを裏返した状態にする。
	  ML::Box2D  draw(0, 0, 128, 128);
	  ML::Box2D  src(0, 0, 128, 128);
	  draw.Offset(this->pos.x, this->pos.y);
	  DG::Image_Draw("Ball", draw, src);
  }

	//★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★
	//以下は基本的に変更不要なメソッド
	//★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★
	//-------------------------------------------------------------------
	//タスク生成窓口
	Object::SP  Object::Create(bool  flagGameEnginePushBack_)
	{
		Object::SP  ob = Object::SP(new  Object());
		if (ob) {
			ob->me = ob;
			if (flagGameEnginePushBack_) {
				ge->PushBack(ob);//ゲームエンジンに登録
			}
			if (!ob->B_Initialize()) {
				ob->Kill();//イニシャライズに失敗したらKill
			}
			return  ob;
		}
		return nullptr;
	}
	//-------------------------------------------------------------------
	bool  Object::B_Initialize()
	{
		return  this->Initialize();
	}
	//-------------------------------------------------------------------
	Object::~Object() { this->B_Finalize(); }
	bool  Object::B_Finalize()
	{
		auto  rtv = this->Finalize();
		return  rtv;
	}
	//-------------------------------------------------------------------
	Object::Object() {	}
	//-------------------------------------------------------------------
	//リソースクラスの生成
	Resource::SP  Resource::Create()
	{
		if (auto sp = instance.lock()) {
			return sp;
		}
		else {
			sp = Resource::SP(new  Resource());
			if (sp) {
				sp->Initialize();
				instance = sp;
			}
			return sp;
		}
	}
	//-------------------------------------------------------------------
	Resource::Resource() {}
	//-------------------------------------------------------------------
	Resource::~Resource() { this->Finalize(); }
}