%name MSLParser
%define LSP_NEEDED

%define MEMBERS\
	virtual ~MSLParser(){}\
	private:\
		yyFlexLexer lexer;\
		MAO* currentMAO;

%define LEX_BODY {return lexer.yylex();}

%define ERROR_BODY {std::cout <<std::endl<<"~ MSL Error Reporting ~"<<std::endl;\
					std::cout<< "-----------------------"<<std::endl;\
					std::cout<< "Error encountered at line: "<<lexer.lineno()<<std::endl;\
					std::cout<< "Last symbol parsed: "<<lexer.YYText()<<std::endl;\
					std::cout<< "Exiting..."<<std::endl;\
					exit(-1);\
					}

//INCLUDES
//----------------------------------------------------------------------
%header{
#include <cstdlib>
#include <FlexLexer.h>
#include <btBulletDynamicsCommon.h>
#include <Kernel/Parsers/MSLProperties.h>
#include <Kernel/Logger.h>
#include <Kernel/World.h>
#include <Factories/MAOFactory.h>
#include <Factories/MLBFactory.h>
%}


//DATA TYPES
//----------------------------------------------------------------------

%union {
	int int_type;
	bool bool_type;
	float float_type;
	std::string* string_type;
	Ogre::Matrix4* pose_type;
	MSLProperties* param_type;
	btVector3* vector3_type;
	MAOValue* maovalue_type;
	MAOProperty* maoproperty_type;
	std::vector<std::string*>* vectorstr_type;
}



//TERMINALS
//----------------------------------------------------------------------

%token < param_type > INTEGER
%token < int_type > T_INTEGER
%token < float_type > FLOAT
%token < int_type > T_FLOAT
%token < string_type > STRING
%token < int_type > T_STRING
%token < bool_type > BOOL
%token < int_type > T_BOOL
%token < int_type > T_POSE
%token < string_type > IDENTIFIER
%token < int_type > ARROW
%token < int_type > DOT

%token < int_type > PARAM_NAME
%token < int_type > PARAM_PATH
%token < int_type > PARAM_SIZE
%token < int_type > PARAM_MARKS
%token < int_type > PARAM_POS
%token < int_type > PARAM_COLOR
%token < int_type > PARAM_WIDTH
%token < int_type > PARAM_HEIGHT
%token < int_type > PARAM_TEXT
%token < int_type > PARAM_ANIM_TYPE
%token < int_type > PARAM_REFERENCE
%token < int_type > PARAM_MAO
%token < int_type > PARAM_TIME
%token < int_type > PARAM_OFFSET
%token < int_type > PARAM_IMPULSE
%token < int_type > PARAM_ANG_AXIS
%token < int_type > PARAM_PROPERTY
%token < int_type > PARAM_ROT_TYPE
%token < int_type > PARAM_LOC_TYPE
%token < int_type > PARAM_ROTATION
%token < int_type > PARAM_LOCATION
%token < int_type > PARAM_TYPE
%token < int_type > PARAM_VALUE
%token < int_type > PARAM_VALUE1
%token < int_type > PARAM_VALUE2
%token < int_type > PARAM_ACTUATOR
%token < int_type > PARAM_KEY
%token < int_type > PARAM_DISTANCE
%token < int_type > PARAM_PROBABILITY
%token < int_type > PARAM_INVERSE
%token < int_type > PARAM_GRAVITY
%token < int_type > PARAM_AXIS
%token < int_type > PARAM_MASS
%token < int_type > PARAM_SHAPE

%token  APPLICATION
%token  MAOWORLD
%token  MAOMARK
%token  MAOMARKSGROUP
%token  MAORENDERABLE2DIMAGE
%token  MAORENDERABLE2DTEXT
%token  MAORENDERABLE3DMODEL


%token  MLBACTUATORADDDYNAMICOBJECT
%token  MLBACTUATORANG
%token  MLBACTUATORCHANGEPOSE
%token  MLBACTUATORDISTANCE
%token  MLBACTUATORPROPERTY
%token  MLBACTUATORQUITAPP
%token  MLBACTUATORRANDOM
%token  MLBACTUATORRELATIVEPOSE
%token  MLBACTUATORSOUND
%token  MLBACTUATORVISIBILITY
%token  MLBACTUATORANIM

%token  MLBCONTROLLERAND
%token  MLBCONTROLLERNAND
%token  MLBCONTROLLERNOR
%token  MLBCONTROLLEROR

%token  MLBSENSORACTUATOR
%token  MLBSENSORALWAYS
%token  MLBSENSORCOLLISION
%token  MLBSENSORDELAY
%token  MLBSENSORKEYBOARD
%token  MLBSENSORNEAR
%token  MLBSENSORPROPERTY
%token  MLBSENSORRANDOM

%token GROUND
%token DYNAMICOBJECT
%token STATICOBJECT


//NON TERMINALS
//----------------------------------------------------------------------
%type < int_type > integer
%type < bool_type > bool
%type < float_type > float
%type < string_type > string
%type < pose_type > pose
%type < string_type > identifier;
%type < vector3_type > vector2di;
%type < vector3_type > vector2df;
%type < vector3_type > vector3di;
%type < vector3_type > vector3df;
%type < maovalue_type > maovalue;
%type < maoproperty_type > maoproperty;

%type < int_type > begin
%type < int_type > maos
%type < int_type > mlbs
%type < int_type > links
%type < int_type > link
%type < vectorstr_type> list_mlbidentifiers

%type < int_type > mao_properties
%type < int_type > mao_property

%type < int_type > ground
%type < int_type > physicobj

%type < param_type > param_dynamicobj

%type < int_type > application

%type < int_type > mao
%type < int_type > def_maomark
%type < int_type > def_maomarksgroup
%type < int_type > def_maorenderable2dimage
%type < int_type > def_maorenderable2dtext
%type < int_type > def_maorenderable3dmodel

%type < param_type > param_maomark
%type < param_type > param_maomarksgroup
%type < param_type > param_maorenderable2dimage
%type < param_type > param_maorenderable2dtext
%type < param_type > param_maorenderable3dmodel

%type < param_type > param_ground

%type < int_type > mlb
%type < int_type > def_mlb
%type < int_type > mlbactuator
%type < int_type > def_mlbactuatoradddynamic
%type < int_type > def_mlbactuatorang
%type < int_type > def_mlbactuatorchangepose
%type < int_type > def_mlbactuatordistance
%type < int_type > def_mlbactuatorproperty
%type < int_type > def_mlbactuatorquitapp
%type < int_type > def_mlbactuatorrandom
%type < int_type > def_mlbactuatorrelativepose
%type < int_type > def_mlbactuatorsound
%type < int_type > def_mlbactuatorvisibility
%type < int_type > def_mlbactuatoranim
%type < param_type > param_mlbactuatoradddynamic
%type < param_type > param_mlbactuatorang
%type < param_type > param_mlbactuatorchangepose
%type < param_type > param_mlbactuatordistance
%type < param_type > param_mlbactuatorproperty
%type < param_type > param_mlbactuatorproperty2
%type < param_type > param_mlbactuatorquitapp
%type < param_type > param_mlbactuatorrandom
%type < param_type > param_mlbactuatorrelativepose
%type < param_type > param_mlbactuatorsound
%type < param_type > param_mlbactuatorvisibility
%type < param_type > param_mlbactuatoranim

%type < int_type > mlbcontroller
%type < int_type > def_mlbcontrollerand
%type < int_type > list_mlbcontrollerand
%type < int_type > def_mlbcontrollernand
%type < int_type > list_mlbcontrollernand
%type < int_type > def_mlbcontrolleror
%type < int_type > list_mlbcontrolleror
%type < int_type > def_mlbcontrollernor
%type < int_type > list_mlbcontrollernor

%type < int_type > mlbsensor
%type < int_type > def_mlbsensoractuator
%type < int_type > def_mlbsensoralways
%type < int_type > def_mlbsensorcollision
%type < int_type > def_mlbsensordelay
%type < int_type > def_mlbsensorkeyboard
%type < int_type > def_mlbsensornear
%type < int_type > def_mlbsensorproperty
%type < int_type > def_mlbsensorrandom
%type < param_type > param_mlbsensoractuator
%type < param_type > param_mlbsensoralways
%type < param_type > param_mlbsensorcollision
%type < param_type > param_mlbsensordelay
%type < param_type > param_mlbsensorkeyboard
%type < param_type > param_mlbsensornear
%type < param_type > param_mlbsensorproperty
%type < param_type > param_mlbsensorproperty2
%type < param_type > param_mlbsensorrandom

//----------------------------------------------------------------------

%start begin

//MAO HEADERS AND DEFINITIONS
//----------------------------------------------------------------------

%%

begin: maos {Logger::getInstance()->out("Parsing completed succesfully! Enjoy your app!");}
     | application maos {Logger::getInstance()->out("Parsing completed succesfully! Enjoy your app!");}
;

application: APPLICATION string {World::getInstance()->setAppName(*$2);}
;

maos: maos mao {}
	| /* empty */ {}
;

mao: def_maomark {}
	| def_maomarksgroup {}
	| def_maorenderable2dimage {}
	| def_maorenderable2dtext {}
	| def_maorenderable3dmodel {}
	| {}
;

mao_properties: mao_properties mao_property {}
	| /* empty */ {}
;

mao_property: T_INTEGER identifier '=' integer {currentMAO->addPropertyInt(*$2,$4);}
                        | T_INTEGER identifier{currentMAO->addPropertyInt(*$2);}
			| T_FLOAT identifier '=' float {currentMAO->addPropertyFloat(*$2,$4);}
			| T_FLOAT identifier  {currentMAO->addPropertyFloat(*$2);}
			| T_BOOL identifier '=' bool {currentMAO->addPropertyBoolean(*$2,$4);}
			| T_BOOL identifier {currentMAO->addPropertyBoolean(*$2);}
			| T_STRING identifier '=' string {currentMAO->addPropertyString(*$2,*$4);}
			| T_STRING identifier {currentMAO->addPropertyString(*$2);}
			| T_POSE identifier '=' pose {currentMAO->addPropertyPose(*$2,*$4);}
			| T_POSE identifier {currentMAO->addPropertyPose(*$2);}
;

//MAO Definitions
//MAOMark
def_maomark: MAOMARK identifier '{' param_maomark { currentMAO = &MAOFactory::getInstance()->addMAOMark(*$2,*$4->string1,$4->float1); ((MAOMark*)currentMAO)->setOffsetMatrix($4->pose1);} mao_properties mlbs links  ground '}' {}
;
param_maomark:  PARAM_PATH '=' string param_maomark {$$ = new MSLProperties(*$4); $$->string1 = $3; } /* REQUIRED */
              | PARAM_SIZE '=' float param_maomark { $$ = new MSLProperties(*$4); $$->float1 = $3;  } /* REQUIRED */
              | PARAM_OFFSET '=' pose param_maomark { $$ = new MSLProperties(*$4); $$->pose1 = $3; } /* OPTIONAL */
	      | /* empty */ {$$ = new MSLProperties();}
;

//MAOMarksGroup
def_maomarksgroup: MAOMARKSGROUP identifier '{' {currentMAO = &MAOFactory::getInstance()->addMAOMarksGroup(*$2);} PARAM_MARKS '=' param_maomarksgroup  mao_properties mlbs links  ground '}' {}
;

param_maomarksgroup: identifier ',' param_maomarksgroup{MAOMark& mark = (MAOMark&)MAOFactory::getInstance()->getMAOPositionator3D(*$1);((MAOMarksGroup*)currentMAO)->addMarktoGroup(mark);}
		    |identifier {MAOMark& mark = (MAOMark&)MAOFactory::getInstance()->getMAOPositionator3D(*$1);((MAOMarksGroup*)currentMAO)->addMarktoGroup(mark);}
;

//MAORenderable2DImage
def_maorenderable2dimage: MAORENDERABLE2DIMAGE identifier '{' param_maorenderable2dimage {currentMAO = &MAOFactory::getInstance()->addMAORenderable2DImage(*$2,*$4->string1,$4->btvector1->x(),$4->btvector1->y(),$4->int3,$4->int4);;} mao_properties mlbs links '}' {}
;
param_maorenderable2dimage: PARAM_PATH '=' string    param_maorenderable2dimage {$$ = new MSLProperties(*$4); $$->string1 = $3; }
                          | PARAM_POS '=' vector2di  param_maorenderable2dimage {$$ = new MSLProperties(*$4); $$->btvector1 = $3;}
                          | PARAM_WIDTH '=' integer  param_maorenderable2dimage {$$ = new MSLProperties(*$4); $$->int3 = $3;}
			  | PARAM_HEIGHT '=' integer param_maorenderable2dimage {$$ = new MSLProperties(*$4); $$->int4 = $3;}
                          | /* empty */ {$$ = new MSLProperties();}
;

def_maorenderable2dtext: MAORENDERABLE2DTEXT identifier '{' param_maorenderable2dtext {currentMAO = &MAOFactory::getInstance()->addMAORenderable2DText(*$2,*$4->string1,$4->int1,*$4->string2,$4->btvector1->x(),$4->btvector1->y()); ((MAORenderable2DText*)currentMAO)->setColor($4->btvector2->x(),$4->btvector2->y(),$4->btvector2->z()); ;} mao_properties mlbs links '}' {}
;
param_maorenderable2dtext: PARAM_PATH '=' string     param_maorenderable2dtext {$$ = new MSLProperties(*$4); $$->string1 = $3; }
                         | PARAM_SIZE '=' integer    param_maorenderable2dtext {$$ = new MSLProperties(*$4); $$->int1 = $3;}
                         | PARAM_TEXT '=' string     param_maorenderable2dtext {$$ = new MSLProperties(*$4); $$->string2 = $3;}
                         | PARAM_POS '=' vector2di   param_maorenderable2dtext {$$ = new MSLProperties(*$4); $$->btvector1 = $3;}
                         | PARAM_COLOR '=' vector3di param_maorenderable2dtext {$$ = new MSLProperties(*$4); $$->btvector2 = $3;}
                         | /* empty */ {$$ = new MSLProperties();}
;

def_maorenderable3dmodel: MAORENDERABLE3DMODEL identifier '{' param_maorenderable3dmodel {currentMAO = &MAOFactory::getInstance()->addMAORenderable3DModel(*$2,$4->float1,*$4->string1,*$4->string2); ;} mao_properties mlbs links physicobj'}' {}
;
param_maorenderable3dmodel: PARAM_SIZE '=' float           param_maorenderable3dmodel {$$ = new MSLProperties(*$4); $$->float1 = $3;} 
                          | PARAM_PATH '=' string          param_maorenderable3dmodel {$$ = new MSLProperties(*$4); $$->string1 = $3; } 
                          | PARAM_REFERENCE '=' identifier param_maorenderable3dmodel {$$ = new MSLProperties(*$4); $$->string2 = $3;} 
                          | /* empty */ {$$ = new MSLProperties();}
;

//Bullet stuff!
ground: GROUND '{' param_ground '}' { PhysicsController::getInstance()->initPhysics(); PhysicsController::getInstance()->setMAOGround(*((MAOPositionator3D*)currentMAO),*$3->string1,$3->float1); }
	| /* empty */ {}
;

param_ground: | PARAM_AXIS '=' string param_ground   {$$ = new MSLProperties(*$4); $$->string1 = $3;}
              | PARAM_GRAVITY '=' float param_ground {$$ = new MSLProperties(*$4); $$->float1 = $3;}
              | /* empty */ {$$ = new MSLProperties();}
;


physicobj: DYNAMICOBJECT '{' param_dynamicobj '}' {PhysicsController::getInstance()->addDynamicRigidBody(*((MAORenderable3D*)currentMAO),$3->float1,$3->pose1,$3->btvector1,*$3->string1);  ((MAORenderable3D*)currentMAO)->setCollisionShapeType(*$3->string1);;}
| STATICOBJECT  '{' PARAM_SHAPE '=' string '}' {PhysicsController::getInstance()->addStaticRigidBody(*((MAORenderable3D*)currentMAO),*$5); ((MAORenderable3D*)currentMAO)->setCollisionShapeType(*$5);;}
	| /* empty */ {}
;

param_dynamicobj:   PARAM_MASS '=' float   param_dynamicobj {$$ = new MSLProperties(*$4); $$->float1 = $3;}
                  | PARAM_SHAPE '=' string param_dynamicobj {$$ = new MSLProperties(*$4); $$->string1 = $3;}
                  | PARAM_OFFSET '=' pose  param_dynamicobj {$$ = new MSLProperties(*$4); $$->pose1 = $3;}
                  | PARAM_IMPULSE '=' vector3df param_dynamicobj {$$ = new MSLProperties(*$4); $$->btvector1 = $3;}
		  | /* empty */ {$$ = new MSLProperties();}
;

//MLB HEADERS
//----------------------------------------------------------------------
mlbs: mlbs mlb {}
		| /* empty */ {}
;

mlb: def_mlb mlbactuator {}
	| def_mlb mlbcontroller {}
	| def_mlb mlbsensor {}
;

def_mlb: {}
;

mlbactuator: def_mlbactuatoradddynamic {}
	| def_mlbactuatorang {}
	| def_mlbactuatorchangepose {}
	| def_mlbactuatordistance {}
	| def_mlbactuatorproperty {}
	| def_mlbactuatorquitapp {}
	| def_mlbactuatorrandom {}
	| def_mlbactuatorrelativepose {}
	| def_mlbactuatorsound {}
	| def_mlbactuatorvisibility {}
	| def_mlbactuatoranim {}
;

mlbcontroller: def_mlbcontrollerand {}
	| def_mlbcontrollernand {}
	| def_mlbcontrolleror {}
	| def_mlbcontrollernor {}
;

mlbsensor: def_mlbsensoractuator {}
	| def_mlbsensoralways {}
	| def_mlbsensorcollision {}
	| def_mlbsensordelay {}
	| def_mlbsensorkeyboard {}
	| def_mlbsensornear {}
	| def_mlbsensorproperty {}
	| def_mlbsensorrandom {}
;




//MLB DEFINITIONS
//----------------------------------------------------------------------

//MLB Actuators
def_mlbactuatoradddynamic: MLBACTUATORADDDYNAMICOBJECT identifier '{' param_mlbactuatoradddynamic '}' {MLBFactory::getInstance()->addMLBActuatorAddDynamicObject(*$2,currentMAO->getName(),*$4->string1,$4->int1,$4->pose1,$4->btvector1); ;}
;
param_mlbactuatoradddynamic: PARAM_MAO '=' identifier  param_mlbactuatoradddynamic {$$ = new MSLProperties(*$4); $$->string1 = $3;}
        | PARAM_TIME '=' integer param_mlbactuatoradddynamic {$$ = new MSLProperties(*$4); $$->int1 = $3;}
	    | PARAM_OFFSET '=' pose param_mlbactuatoradddynamic {$$ = new MSLProperties(*$4); $$->pose1 = $3;}
	    | PARAM_IMPULSE '=' vector3df param_mlbactuatoradddynamic {$$ = new MSLProperties(*$4); $$->btvector1 = $3;}
	    | /*empty*/ {$$ = new MSLProperties();}
;

def_mlbactuatorang: MLBACTUATORANG identifier '{' param_mlbactuatorang '}' {MLBFactory::getInstance()->addMLBActuatorAng(*$2,currentMAO->getName(),*$4->maoproperty1, *$4->string2); ;}
;
param_mlbactuatorang: PARAM_PROPERTY '=' maoproperty param_mlbactuatorang {$$ = new MSLProperties(*$4); $$->maoproperty1 = $3;}
                    | PARAM_ANG_AXIS '=' string    param_mlbactuatorang {$$ = new MSLProperties(*$4); $$->string2 = $3;}
	                | /*empty*/ {$$ = new MSLProperties();}
;

def_mlbactuatorchangepose: MLBACTUATORCHANGEPOSE identifier '{'  param_mlbactuatorchangepose '}' {MLBFactory::getInstance()->addMLBActuatorChangePose(*$2, currentMAO->getName(),*$4->string1, $4->btvector1, *$4->string2, $4->btvector2); ;}
;
param_mlbactuatorchangepose: param_mlbactuatorchangepose param_mlbactuatorchangepose {$$ = new MSLProperties(*$1); $$->fill(*$2); ; ;}
| PARAM_LOC_TYPE '=' string PARAM_LOCATION '=' vector3df {$$ = new MSLProperties(); $$->string1 = $3; $$->btvector1 = $6;}
| PARAM_ROT_TYPE '=' string PARAM_ROTATION '=' vector3df {$$ = new MSLProperties(); $$->string2 = $3; $$->btvector2 = $6;}
;

def_mlbactuatordistance: MLBACTUATORDISTANCE identifier '{'  param_mlbactuatordistance '}' {MLBFactory::getInstance()->addMLBActuatorDistance(*$2,currentMAO->getName(),*$4->string1, *$4->maoproperty1); ;}
;
param_mlbactuatordistance: PARAM_MAO '=' identifier param_mlbactuatordistance {$$ = new MSLProperties(*$4); $$->string1 = $3;}
                           | PARAM_PROPERTY '=' maoproperty param_mlbactuatordistance {$$ = new MSLProperties(*$4); $$->maoproperty1 = $3;}
                           | /*empty*/ {$$ = new MSLProperties();}
;

def_mlbactuatorproperty: MLBACTUATORPROPERTY identifier '{'  param_mlbactuatorproperty '}' {MLBFactory::getInstance()->addMLBActuatorProperty(*$2,currentMAO->getName(),*$4->maoproperty1, *$4->maovalue1,*$4->string1); ;}
                       | MLBACTUATORPROPERTY identifier '{'  param_mlbactuatorproperty2 '}' {MLBFactory::getInstance()->addMLBActuatorProperty(*$2,currentMAO->getName(),*$4->maoproperty1, *$4->maoproperty2,*$4->string1); ;}
;
param_mlbactuatorproperty: PARAM_TYPE '=' string PARAM_PROPERTY '=' maoproperty PARAM_VALUE '=' maovalue {$$ = new MSLProperties(); $$ ->string1 = $3; $$ ->maoproperty1 = $6; $$ -> maovalue1 = $9;}
;
param_mlbactuatorproperty2: PARAM_TYPE '=' string PARAM_PROPERTY '=' maoproperty PARAM_VALUE '=' maoproperty {$$ = new MSLProperties(); $$ ->string1 = $3; $$ ->maoproperty1 = $6; $$ -> maoproperty2 = $9;}
;

def_mlbactuatorquitapp: MLBACTUATORQUITAPP identifier '{'  param_mlbactuatorquitapp '}' {MLBFactory::getInstance()->addMLBActuatorQuitApp(*$2,currentMAO->getName()); ;}
;
param_mlbactuatorquitapp: { $$ = new MSLProperties();}
;

def_mlbactuatorrandom: MLBACTUATORRANDOM identifier '{'  param_mlbactuatorrandom '}' {MLBFactory::getInstance()->addMLBActuatorRandom(*$2, currentMAO->getName(),*$4->maoproperty1); ;}
;
param_mlbactuatorrandom: PARAM_PROPERTY '=' maoproperty {$$ = new MSLProperties(); $$ -> maoproperty1 = $3;}
;

def_mlbactuatorrelativepose: MLBACTUATORRELATIVEPOSE identifier '{'  param_mlbactuatorrelativepose '}' {MLBFactory::getInstance()->addMLBActuatorRelativePose(*$2,currentMAO->getName(),*$4->string1, *$4->maoproperty1, $4->bool1); ;}
;
param_mlbactuatorrelativepose: PARAM_REFERENCE '=' identifier param_mlbactuatorrelativepose {$$ = new MSLProperties(*$4); $$->string1 = $3;}
                             | PARAM_PROPERTY '=' maoproperty param_mlbactuatorrelativepose {$$ = new MSLProperties(*$4); $$->maoproperty1 = $3;}
                             | PARAM_INVERSE '=' bool param_mlbactuatorrelativepose {$$ = new MSLProperties(*$4); $$->bool1 = $3;}
                             | /*empty*/ {$$ = new MSLProperties();}
;

def_mlbactuatorsound: MLBACTUATORSOUND identifier '{'  param_mlbactuatorsound '}' {MLBFactory::getInstance()->addMLBActuatorSound(*$2, currentMAO->getName(),*$4->string1); ;}
;
param_mlbactuatorsound: PARAM_PATH '=' string {$$ = new MSLProperties(); $$->string1 = $3; }
;

def_mlbactuatorvisibility: MLBACTUATORVISIBILITY identifier '{'  param_mlbactuatorvisibility '}' {MLBFactory::getInstance()->addMLBActuatorVisibility(*$2, currentMAO->getName(), $4->bool1); ;}
;
param_mlbactuatorvisibility: PARAM_VALUE '=' bool {$$ = new MSLProperties(); $$ -> bool1 = $3;}
;

def_mlbactuatoranim: MLBACTUATORANIM identifier '{' param_mlbactuatoranim '}' { MLBFactory::getInstance()->addMLBActuatorAnim(*$2, currentMAO->getName(), *$4->string1, $4->string2); ;}
;
param_mlbactuatoranim: PARAM_TYPE '=' string PARAM_ANIM_TYPE '=' string {$$ = new MSLProperties(); $$->string1 = $3; $$ -> string2 = $6;}
	| PARAM_TYPE '=' string { $$ = new MSLProperties(); $$->string1 = $3;}
;

//MLB Controllers
def_mlbcontrollerand: MLBCONTROLLERAND list_mlbcontrollerand {}
;
list_mlbcontrollerand: list_mlbcontrollerand ',' identifier {MLBFactory::getInstance()->addMLBControllerAND(*$3, currentMAO->getName());}
	| identifier {MLBFactory::getInstance()->addMLBControllerAND(*$1, currentMAO->getName());}
	| /*empty*/ {}
;

def_mlbcontrollernand: MLBCONTROLLERNAND list_mlbcontrollernand {}
;
list_mlbcontrollernand: list_mlbcontrollernand ',' identifier {MLBFactory::getInstance()->addMLBControllerNAND(*$3, currentMAO->getName());}
	| identifier {MLBFactory::getInstance()->addMLBControllerNAND(*$1, currentMAO->getName());}
	| /*empty*/ {}
;

def_mlbcontrolleror: MLBCONTROLLEROR list_mlbcontrolleror {}
;
list_mlbcontrolleror: list_mlbcontrolleror ',' identifier {MLBFactory::getInstance()->addMLBControllerOR(*$3, currentMAO->getName());}
	| identifier {MLBFactory::getInstance()->addMLBControllerOR(*$1, currentMAO->getName());}
	| /*empty*/ {}
;

def_mlbcontrollernor: MLBCONTROLLERNOR list_mlbcontrollernor {}
;
list_mlbcontrollernor: list_mlbcontrollernor ',' identifier {MLBFactory::getInstance()->addMLBControllerNOR(*$3, currentMAO->getName());}
	| identifier {MLBFactory::getInstance()->addMLBControllerNOR(*$1, currentMAO->getName());}
	| /*empty*/ {}
;


//MLB Sensors

def_mlbsensoractuator: MLBSENSORACTUATOR identifier '{'  param_mlbsensoractuator '}' {MLBFactory::getInstance()->addMLBSensorActuator(*$2, currentMAO->getName(), *$4->string1); ;}
;
param_mlbsensoractuator: PARAM_ACTUATOR '=' identifier {$$ = new MSLProperties(); $$ -> string1 = $3;}
;

def_mlbsensoralways: MLBSENSORALWAYS identifier '{'  param_mlbsensoralways '}' {MLBFactory::getInstance()->addMLBSensorAlways(*$2, currentMAO->getName()); ;}
;
param_mlbsensoralways: {$$ = new MSLProperties();}
;

def_mlbsensorcollision: MLBSENSORCOLLISION identifier '{'  param_mlbsensorcollision '}' {MLBFactory::getInstance()->addMLBSensorCollision(*$2,currentMAO->getName(),*$4->string1); ;}
;
param_mlbsensorcollision: PARAM_PROPERTY '=' identifier { $$ = new MSLProperties(); $$ -> string1 = $3;}
;

def_mlbsensordelay: MLBSENSORDELAY identifier '{'  param_mlbsensordelay '}' {MLBFactory::getInstance()->addMLBSensorDelay(*$2, currentMAO->getName(),$4->int1); ;}
;
param_mlbsensordelay: PARAM_TIME '=' integer {$$ = new MSLProperties(); $$ -> int1 = $3;}
;

def_mlbsensorkeyboard: MLBSENSORKEYBOARD identifier '{' param_mlbsensorkeyboard '}' {MLBFactory::getInstance()->addMLBSensorKeyboard(*$2, currentMAO->getName(),*$4->string1, *$4->string2); ;}
;
param_mlbsensorkeyboard: PARAM_TYPE '=' string param_mlbsensorkeyboard {$$ = new MSLProperties(*$4); $$->string1 = $3;}
                         | PARAM_KEY '=' string param_mlbsensorkeyboard {$$ = new MSLProperties(*$4); $$->string2 = $3;}
                         | /* Empty */ {$$ = new MSLProperties();}
;

def_mlbsensornear: MLBSENSORNEAR identifier '{' param_mlbsensornear '}' {MLBFactory::getInstance()->addMLBSensorNear(*$2, currentMAO->getName(),*$4->string1,$4->float1); ;}
;
param_mlbsensornear: PARAM_PROPERTY '=' identifier param_mlbsensornear {$$ = new MSLProperties(*$4); $$->string1 = $3;}
                   | PARAM_DISTANCE '=' float param_mlbsensornear {$$ = new MSLProperties(*$4); $$->float1 = $3;}
                   | /* Empty */ {$$ = new MSLProperties();}
;

def_mlbsensorproperty: MLBSENSORPROPERTY identifier '{' param_mlbsensorproperty '}' {MLBFactory::getInstance()->addMLBSensorProperty(*$2, currentMAO->getName(),*$4->string1, *$4->maoproperty1, $4->maovalue1, $4->maovalue2); ;}
| MLBSENSORPROPERTY identifier '{' param_mlbsensorproperty2 '}' {MLBFactory::getInstance()->addMLBSensorProperty(*$2, currentMAO->getName(),*$4->string1, *$4->maoproperty1, $4->maoproperty2); ;}
;
param_mlbsensorproperty: PARAM_TYPE '=' string  PARAM_PROPERTY '=' maoproperty PARAM_VALUE '=' maovalue{ $$ = new MSLProperties(); $$->string1 = $3; $$->maoproperty1 = $6; $$->maovalue1 = $9;}
						| PARAM_TYPE '=' string PARAM_PROPERTY '=' maoproperty PARAM_VALUE1 '=' maovalue PARAM_VALUE2 '=' maovalue{ $$ = new MSLProperties(); $$->string1 = $3; $$->maoproperty1 = $6; $$->maovalue1 = $9; $$->maovalue2 = $12;}
;
param_mlbsensorproperty2: PARAM_TYPE '=' string PARAM_PROPERTY '=' maoproperty PARAM_VALUE '=' maoproperty {$$ = new MSLProperties(); $$->string1 = $3; $$->maoproperty1 = $6; $$->maoproperty2 = $9;}
;

def_mlbsensorrandom: MLBSENSORRANDOM identifier '{' param_mlbsensorrandom '}' {MLBFactory::getInstance()->addMLBSensorRandom(*$2,currentMAO->getName(),$4->float1); ;}
;
param_mlbsensorrandom: PARAM_PROBABILITY '=' float {$$ = new MSLProperties(); $$->float1 = $3;}
;

//LINKS DEFINITIONS
//----------------------------------------------------------------------

links: links link {}
		| /* empty */ {}
;
link:  list_mlbidentifiers ARROW identifier ARROW list_mlbidentifiers {
				for(unsigned int i=0;i<$1->size();i++){
					MLBFactory::getInstance()->addMLBLink(currentMAO->getName(),*($1->at(i)),*$3);
				}

				for(unsigned int i=0;i<$5->size();i++){
					MLBFactory::getInstance()->addMLBLink(currentMAO->getName(),*$3,*($5->at(i)));
				}
				; ;}
	| list_mlbidentifiers ARROW list_mlbidentifiers {
				for(unsigned int i=0;i<$1->size();i++){
					for(unsigned int j=0;j<$3->size();j++){
						MLBFactory::getInstance()->addMLBLink(currentMAO->getName(),*($1->at(i)),*($3->at(j)));
					}
				}
				; }

;
list_mlbidentifiers: identifier ',' list_mlbidentifiers {
					$$ = new std::vector<std::string*>(); $$->push_back($1);
					for(unsigned int i=0;i<$3->size();i++){
						$$->push_back($3->at(i));
					}
					;
					}
		| identifier {$$ = new std::vector<std::string*>(); $$->push_back($1);}
;


//BASIC DATA TYPES DEFINITION
//----------------------------------------------------------------------

integer : INTEGER { $$ = atoi(lexer.YYText());}
;

bool : BOOL {if(strcmp(lexer.YYText(),"False")==0) $$ = false; else $$ = true;}
;

float : FLOAT {$$ = atof(lexer.YYText());}
;

string : STRING {int l = strlen(lexer.YYText()); $$ = new std::string(lexer.YYText()+1,l-2);}
;

pose : 	float float float float float float float float	float float float float	float float float float {float* f = new float[16];f[0]=$1; f[1]=$2;f[2]=$3;f[3]=$4;
f[4]=$5; f[5]=$6;f[6]=$7;f[7]=$8;
f[8]=$9; f[9]=$10;f[10]=$11;f[11]=$12;
f[12]=$13; f[13]=$14;f[14]=$15;f[15]=$16;
Ogre::Matrix4* m = new Ogre::Matrix4(f[0], f[4], f[8], f[12], 
									f[1], f[5], f[9], f[13],
									f[2], f[6], f[10], f[14],
									f[3], f[7], f[11], f[15]); $$ = m;}
;

maovalue: integer {$$ = new MAOValue(MAOPROPERTY_INT, $1);}
		| bool {$$ = new MAOValue(MAOPROPERTY_BOOLEAN, $1)}
		| float {$$ = new MAOValue(MAOPROPERTY_FLOAT, $1)}
		| string {$$ = new MAOValue(MAOPROPERTY_STRING, $1)}
		| pose {$$ = new MAOValue(MAOPROPERTY_POSE, $1)}
;

maoproperty: identifier DOT identifier { $$ = &MAOFactory::getInstance()->findProperty(*$1,*$3); }
			|identifier {$$ = &MAOFactory::getInstance()->findProperty(currentMAO->getName(),*$1);}
;

vector2di: '(' integer ',' integer ')' { $$ = new btVector3($2,$4,-1);}
;
vector2df: '(' float ',' float ')' { $$ = new btVector3($2,$4,-1);}
;

vector3di: '(' integer ',' integer ',' integer ')' {$$ = new btVector3($2,$4,$6);}
;

vector3df: '(' float ',' float ',' float ')' {$$ = new btVector3($2,$4,$6);}
;

identifier : IDENTIFIER { $$ = new std::string(lexer.YYText());}
;

%%
