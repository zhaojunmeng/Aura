%option c++
%option noyywrap

%{
#include <Kernel/Parsers/MSLParser.h>
using namespace std;
%}

%x COMMENT

DIGIT [0-9]
ID [A-Za-z][A-Za-z0-9_]*
SIGN {-|+}

%%

"Application"				{return MSLParser::APPLICATION;}
"Mark" 						{return MSLParser::MAOMARK;}
"MarksGroup" 				{return MSLParser::MAOMARKSGROUP;}
"Image" 			{return MSLParser::MAORENDERABLE2DIMAGE;}
"Text" 			{return MSLParser::MAORENDERABLE2DTEXT;}
"Model" 			{return MSLParser::MAORENDERABLE3DMODEL;}

"ActuatorAddDynamicObject" 	{return MSLParser::MLBACTUATORADDDYNAMICOBJECT;}
"ActuatorAng" 				{return MSLParser::MLBACTUATORANG;}
"ActuatorChangePose" 		{return MSLParser::MLBACTUATORCHANGEPOSE;}
"ActuatorDistance" 			{return MSLParser::MLBACTUATORDISTANCE;}
"ActuatorProperty" 			{return MSLParser::MLBACTUATORPROPERTY;}
"ActuatorQuitApp" 			{return MSLParser::MLBACTUATORQUITAPP;}
"ActuatorRandom" 			{return MSLParser::MLBACTUATORRANDOM;}
"ActuatorRelativePose" 		{return MSLParser::MLBACTUATORRELATIVEPOSE;}
"ActuatorSound" 				{return MSLParser::MLBACTUATORSOUND;}
"ActuatorVisibility" 		{return MSLParser::MLBACTUATORVISIBILITY;}
"ActuatorAnim" 				{return MSLParser::MLBACTUATORANIM;}

"AND" 				{return MSLParser::MLBCONTROLLERAND;}
"NAND" 			{return MSLParser::MLBCONTROLLERNAND;}
"NOR" 				{return MSLParser::MLBCONTROLLERNOR;}
"OR" 				{return MSLParser::MLBCONTROLLEROR;}

"SensorActuator" 			{return MSLParser::MLBSENSORACTUATOR;}
"SensorAlways" 				{return MSLParser::MLBSENSORALWAYS;}
"SensorCollision"			{return MSLParser::MLBSENSORCOLLISION;}
"SensorDelay" 				{return MSLParser::MLBSENSORDELAY;}
"SensorKeyboard" 			{return MSLParser::MLBSENSORKEYBOARD;}
"SensorNear"					{return MSLParser::MLBSENSORNEAR;}
"SensorProperty" 			{return MSLParser::MLBSENSORPROPERTY;}
"SensorRandom" 				{return MSLParser::MLBSENSORRANDOM;}

"Ground"						{return MSLParser::GROUND;}
"DynamicObject"					{return MSLParser::DYNAMICOBJECT;}
"StaticObject"					{return MSLParser::STATICOBJECT;}


"name" 							{return MSLParser::PARAM_NAME;}
"path"							{return MSLParser::PARAM_PATH;}
"size"							{return MSLParser::PARAM_SIZE;}
"marks"							{return MSLParser::PARAM_MARKS;}
"pos"							{return MSLParser::PARAM_POS;}
"color"							{return MSLParser::PARAM_COLOR;}
"width"							{return MSLParser::PARAM_WIDTH;}
"height"						{return MSLParser::PARAM_HEIGHT;}
"text"							{return MSLParser::PARAM_TEXT;}
"anim_type"						{return MSLParser::PARAM_ANIM_TYPE;}
"reference"						{return MSLParser::PARAM_REFERENCE;}
"mao"							{return MSLParser::PARAM_MAO;}
"time"							{return MSLParser::PARAM_TIME;}
"offset"						{return MSLParser::PARAM_OFFSET;}
"impulse"						{return MSLParser::PARAM_IMPULSE;}
"ang_axis"						{return MSLParser::PARAM_ANG_AXIS;}
"property"						{return MSLParser::PARAM_PROPERTY;}
"rot_type"						{return MSLParser::PARAM_ROT_TYPE;}
"rotation"						{return MSLParser::PARAM_ROTATION;}
"loc_type"						{return MSLParser::PARAM_LOC_TYPE;}
"location"						{return MSLParser::PARAM_LOCATION;}
"type"							{return MSLParser::PARAM_TYPE;}
"value"							{return MSLParser::PARAM_VALUE;}
"value1"						{return MSLParser::PARAM_VALUE1;}
"value2"						{return MSLParser::PARAM_VALUE2;}
"actuator"						{return MSLParser::PARAM_ACTUATOR;}
"key"							{return MSLParser::PARAM_KEY;}
"distance"						{return MSLParser::PARAM_DISTANCE;}
"probability"					{return MSLParser::PARAM_PROBABILITY;}
"inverse"						{return MSLParser::PARAM_INVERSE;}
"gravity"						{return MSLParser::PARAM_GRAVITY;}
"axis"							{return MSLParser::PARAM_AXIS;}
"mass"							{return MSLParser::PARAM_MASS;}
"shape"							{return MSLParser::PARAM_SHAPE;}

"int"							{return MSLParser::T_INTEGER;}
"float"							{return MSLParser::T_FLOAT;}
"bool"							{return MSLParser::T_BOOL;}
"string"						{return MSLParser::T_STRING;}
"pose"							{return MSLParser::T_POSE;}

"/*"							{BEGIN(COMMENT);}
<COMMENT>"*/"					{BEGIN(INITIAL);}
<COMMENT>[\t ]*				{}
<COMMENT>\n                                       {yylineno++;}
<COMMENT>.						{}

"->"							{return MSLParser::ARROW;}
"."								{return MSLParser::DOT;}
\"[^\n\t]*\"					{return MSLParser::STRING;}
"-"?{DIGIT}*"."{DIGIT}*		{return MSLParser::FLOAT;}
"-"?{DIGIT}*					{return MSLParser::INTEGER;}
"False"		 					{return MSLParser::BOOL;}
"True"							{return MSLParser::BOOL;}
{ID} 							{return MSLParser::IDENTIFIER;}
\n                                                      {yylineno++;}
[ \t]							{/*Ignore every blank space*/}
.								{/*Any other literal, just return it! */ return yytext[0];}
<<EOF>>							{yyterminate();}

%%
