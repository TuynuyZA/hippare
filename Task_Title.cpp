//-------------------------------------------------------------------
//^CgζΚ
//-------------------------------------------------------------------
#include  "MyPG.h"
#include  "Task_Title.h"
#include  "Task_Game.h"

#include "easing.h"
namespace  Title
{
	Resource::WP  Resource::instance;
	//-------------------------------------------------------------------
	//\[XΜϊ»
	bool  Resource::Initialize()
	{
		DG::Image_Create("back", "./data/image/back.jpg");


		this->imageName = "TitleLogoImg";
		DG::Image_Create(this->imageName, "./data/image/title2.png");

		return true;
	}
	//-------------------------------------------------------------------
	//\[XΜπϊ
	bool  Resource::Finalize()
	{
		DG::Image_Erase(this->imageName);
		return true;
	}
	//-------------------------------------------------------------------
	//uϊ»v^XNΆ¬ΙPρΎ―s€
	bool  Object::Initialize()
	{
		//X[p[NXϊ»
		__super::Initialize(defGroupName, defName, true);
		//\[XNXΆ¬or\[X€L
		this->res = Resource::Create();

		//f[^ϊ»
    easing::Create("titleLog0", easing::EASINGTYPE::BACKOUT, -100, 300, 100);
    easing::Start("titleLog0");
    this->logoPosX = easing::GetPos("titleLog0");

		//^XNΜΆ¬

		return  true;
	}
	//-------------------------------------------------------------------
	//uIΉv^XNΑΕΙPρΎ―s€
	bool  Object::Finalize()
	{

		if (!ge->QuitFlag() && this->nextTaskCreate) {
			//ψ«p¬^XNΜΆ¬
			auto nextTask = Game::Object::Create(true);
		}

		return  true;
	}

	//-------------------------------------------------------------------
	//uXVvPt[Ιs€
	void  Object::UpDate()
	{
		auto in = DI::GPad_GetState("P1");

    //f[^^XNπϊ
    this->logoPosX = easing::GetPos("titleLog0");

    easing::UpDate();
		if (easing::GetState("titleLog0") == easing::EQ_STATE::EQ_END) {
			if (in.ST.down) {
				//©gΙΑΕvΏ
				this->Kill();
			}
		}
	}
	//-------------------------------------------------------------------
	//uQc`ζvPt[Ιs€
	void  Object::Render2D_AF()
	{
		ML::Box2D  draw(0, 0, 1024, 1024);
		ML::Box2D  src(0, 0, 620, 439);
		DG::Image_Draw("back", draw, src);

		/*draw = ML::Box2D(-300, -370, 599, 741);
		src =  ML::Box2D(0, 0, 425, 283);
		draw.Offset((int)this->logoPosX, 1024/2);
		DG::Image_Draw(this->res->imageName, draw, src);*/

		draw = ML::Box2D(0, 0, 425, 283);
		src = ML::Box2D(0, 0, 425, 283);
		draw.Offset((int)this->logoPosX, 1024 / 2 - 283/2);
		DG::Image_Draw(this->res->imageName, draw, src);
	}

	//
	//ΘΊΝξ{IΙΟXsvΘ\bh
	//
	//-------------------------------------------------------------------
	//^XNΆ¬ϋ
	Object::SP  Object::Create(bool  flagGameEnginePushBack_)
	{
		Object::SP  ob = Object::SP(new  Object());
		if (ob) {
			ob->me = ob;
			if (flagGameEnginePushBack_) {
				ge->PushBack(ob);//Q[GWΙo^
			}
			if (!ob->B_Initialize()) {
				ob->Kill();//CjVCYΙΈs΅½ηKill
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
	//\[XNXΜΆ¬
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