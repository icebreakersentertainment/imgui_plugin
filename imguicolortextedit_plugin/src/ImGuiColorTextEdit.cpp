#include "Platform.hpp"
#include "Types.hpp"

#include <TextEditor.h>

#include "ImGuiColorTextEdit.hpp"

#include "../../include/GenericComponentContainer.hpp"
#include "../../include/imguicolortextedit/TextEditor.hpp"

#include "graphics/gui/IWindow.hpp"

#include "BindingDelegateUtilities.hpp"

#include "scripting/IScriptingEngine.hpp"

namespace ice_engine
{

class GameEngine;

namespace imguicolortextedit
{

ImGuiColorTextEdit::ImGuiColorTextEdit(
	utilities::Properties* properties,
	fs::IFileSystem* fileSystem,
	logger::ILogger* logger,
	graphics::IGraphicsEngine* graphicsEngine,
	pathfinding::IPathfindingEngine* pathfindingEngine,
	physics::IPhysicsEngine* physicsEngine,
	scripting::IScriptingEngine* scriptingEngine,
	audio::IAudioEngine* audioEngine,
	networking::INetworkingEngine* networkingEngine,
	GameEngine* gameEngine
)
	:
	logger_(logger),
	scriptingEngine_(scriptingEngine),
	gameEngine_(gameEngine)
{
}

void ImGuiColorTextEdit::bind()
{
    scriptingEngine_->registerEnum("SyntaxHighlighting");
    scriptingEngine_->registerEnumValue("SyntaxHighlighting", "None", graphics::gui::SyntaxHighlighting::None);
    scriptingEngine_->registerEnumValue("SyntaxHighlighting", "CPlusPlus", graphics::gui::SyntaxHighlighting::CPlusPlus);
    scriptingEngine_->registerEnumValue("SyntaxHighlighting", "GLSL", graphics::gui::SyntaxHighlighting::GLSL);
    scriptingEngine_->registerEnumValue("SyntaxHighlighting", "HLSL", graphics::gui::SyntaxHighlighting::HLSL);
    scriptingEngine_->registerEnumValue("SyntaxHighlighting", "C", graphics::gui::SyntaxHighlighting::C);
    scriptingEngine_->registerEnumValue("SyntaxHighlighting", "SQL", graphics::gui::SyntaxHighlighting::SQL);
    scriptingEngine_->registerEnumValue("SyntaxHighlighting", "AngelScript", graphics::gui::SyntaxHighlighting::AngelScript);
    scriptingEngine_->registerEnumValue("SyntaxHighlighting", "Lua", graphics::gui::SyntaxHighlighting::Lua);

    scriptingEngine_->registerObjectType("ITextEditor", 0, asOBJ_REF | asOBJ_NOCOUNT);
    scriptingEngine_->registerObjectMethod("ITextEditor", "IComponent@ opImplCast()", asFUNCTION((refCast<graphics::gui::ITextEditor, graphics::gui::IComponent>)), asCALL_CDECL_OBJLAST);
    scriptingEngine_->registerClassMethod("ITextEditor", "const string& text() const",
                                          asMETHOD(graphics::gui::ITextEditor, text));
    scriptingEngine_->registerClassMethod("ITextEditor", "void setText(const string& in)",
                                          asMETHOD(graphics::gui::ITextEditor, setText));
    scriptingEngine_->registerClassMethod("ITextEditor", "void setSyntaxHighlighting(const SyntaxHighlighting)",
                                          asMETHOD(graphics::gui::ITextEditor, setSyntaxHighlighting));
    scriptingEngine_->registerClassMethod("ITextEditor", "SyntaxHighlighting syntaxHighlighting() const",
                                          asMETHOD(graphics::gui::ITextEditor, syntaxHighlighting));
    scriptingEngine_->registerClassMethod("ITextEditor", "void setCursorPosition(const int32, const int32)",
                                          asMETHOD(graphics::gui::ITextEditor, setCursorPosition));
//    COMPONENT_CLASS_METHODS("ITextEditor", graphics::gui::ITextEditor)
//    scriptingEngine_->registerObjectMethod(
//            "ITextEditor",
//            "void setOnChangeCallback(TextEditorOnChangeCallback@ callback)",
//            asMETHODPR(GameEngine, setOnChangeCallback, (graphics::gui::ITextEditor*, void*), void),
//            asCALL_THISCALL_OBJFIRST,
//            gameEngine_
//    );

    scriptingEngine_->registerObjectType("ImGuiColorTextEdit", 0, asOBJ_REF | asOBJ_NOCOUNT);
    scriptingEngine_->registerGlobalProperty("ImGuiColorTextEdit imguicolortextedit", this);
    scriptingEngine_->registerClassMethod(
            "ImGuiColorTextEdit",
            "ITextEditor@ createTextEditor(IWindow@, const string)",
            asMETHODPR(ImGuiColorTextEdit, createTextEditor, (graphics::gui::IWindow*, const std::string), graphics::gui::ITextEditor*)
    );
    scriptingEngine_->registerClassMethod(
            "ImGuiColorTextEdit",
            "ITextEditor@ createTextEditor(IWindow@, const uint32, const uint32, const uint32, const uint32, const string)",
            asMETHODPR(ImGuiColorTextEdit, createTextEditor, (graphics::gui::IWindow*, const uint32, const uint32, const uint32, const uint32, const std::string), graphics::gui::ITextEditor*)
    );
    
//    scriptingEngine_->registerEnum("JsonValueType");
//    scriptingEngine_->registerEnumValue("JsonValueType", "nullValue", Json::ValueType::nullValue);
//    scriptingEngine_->registerEnumValue("JsonValueType", "intValue", Json::ValueType::intValue);
//    scriptingEngine_->registerEnumValue("JsonValueType", "uintValue", Json::ValueType::uintValue);
//    scriptingEngine_->registerEnumValue("JsonValueType", "realValue", Json::ValueType::realValue);
//    scriptingEngine_->registerEnumValue("JsonValueType", "stringValue", Json::ValueType::stringValue);
//    scriptingEngine_->registerEnumValue("JsonValueType", "booleanValue", Json::ValueType::booleanValue);
//    scriptingEngine_->registerEnumValue("JsonValueType", "arrayValue", Json::ValueType::arrayValue);
//    scriptingEngine_->registerEnumValue("JsonValueType", "objectValue", Json::ValueType::objectValue);
//
//	scriptingEngine_->registerObjectType("JsonValue", sizeof(Json::Value), asOBJ_VALUE | asOBJ_APP_CLASS_ALLINTS | asGetTypeTraits<Json::Value>());
//    scriptingEngine_->registerObjectBehaviour("JsonValue", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(DefaultConstructor<Json::Value>), asCALL_CDECL_OBJFIRST);
//    scriptingEngine_->registerObjectBehaviour("JsonValue", asBEHAVE_CONSTRUCT, "void f(JsonValueType type)", asFUNCTION(InitConstructorNoForward<Json::Value COMMA Json::ValueType>), asCALL_CDECL_OBJFIRST);
//    scriptingEngine_->registerObjectBehaviour("JsonValue", asBEHAVE_CONSTRUCT, "void f(int)", asFUNCTION(InitConstructorNoForward<Json::Value COMMA int>), asCALL_CDECL_OBJFIRST);
//    scriptingEngine_->registerObjectBehaviour("JsonValue", asBEHAVE_CONSTRUCT, "void f(uint)", asFUNCTION(InitConstructorNoForward<Json::Value COMMA uint>), asCALL_CDECL_OBJFIRST);
//    scriptingEngine_->registerObjectBehaviour("JsonValue", asBEHAVE_CONSTRUCT, "void f(double)", asFUNCTION(InitConstructorNoForward<Json::Value COMMA double>), asCALL_CDECL_OBJFIRST);
//    scriptingEngine_->registerObjectBehaviour("JsonValue", asBEHAVE_CONSTRUCT, "void f(bool)", asFUNCTION(InitConstructorNoForward<Json::Value COMMA bool>), asCALL_CDECL_OBJFIRST);
//    scriptingEngine_->registerObjectBehaviour("JsonValue", asBEHAVE_CONSTRUCT, "void f(const string& in)", asFUNCTION(InitConstructorNoForward<Json::Value COMMA const std::string&>), asCALL_CDECL_OBJFIRST);
//    scriptingEngine_->registerObjectBehaviour("JsonValue", asBEHAVE_CONSTRUCT, "void f(const JsonValue& in)", asFUNCTION(CopyConstructor<Json::Value>), asCALL_CDECL_OBJFIRST);
//	scriptingEngine_->registerObjectBehaviour("JsonValue", asBEHAVE_DESTRUCT, "void f()", asFUNCTION(DefaultDestructor<Json::Value>), asCALL_CDECL_OBJFIRST);
//
//	scriptingEngine_->registerObjectMethod("JsonValue", "JsonValue& opAssign(const JsonValue& in)", asFUNCTION(defaultAssignmentOperator<Json::Value>), asCALL_CDECL_OBJLAST);
//    scriptingEngine_->registerClassMethod("JsonValue", "JsonValue& opIndex(const string& in)", asMETHODPR(Json::Value, operator[], (const JSONCPP_STRING&), Json::Value&));
//    scriptingEngine_->registerClassMethod("JsonValue", "const JsonValue& opIndex(const string& in) const", asMETHODPR(Json::Value, operator[], (const JSONCPP_STRING&) const, const Json::Value&));
//    scriptingEngine_->registerClassMethod("JsonValue", "JsonValue& opIndex(uint)", asMETHODPR(Json::Value, operator[], (Json::ArrayIndex), Json::Value&));
//    scriptingEngine_->registerClassMethod("JsonValue", "const JsonValue& opIndex(uint) const", asMETHODPR(Json::Value, operator[], (Json::ArrayIndex ) const, const Json::Value&));
//
//    scriptingEngine_->registerClassMethod("JsonValue", "int asInt() const", asMETHOD(Json::Value, asInt));
//    scriptingEngine_->registerClassMethod("JsonValue", "uint asUInt() const", asMETHOD(Json::Value, asUInt));
//    scriptingEngine_->registerClassMethod("JsonValue", "double asDouble() const", asMETHOD(Json::Value, asDouble));
//    scriptingEngine_->registerClassMethod("JsonValue", "bool asBool() const", asMETHOD(Json::Value, asBool));
//    scriptingEngine_->registerClassMethod("JsonValue", "string asString() const", asMETHOD(Json::Value, asString));
//    scriptingEngine_->registerClassMethod("JsonValue", "uint size() const", asMETHOD(Json::Value, size));
//    scriptingEngine_->registerClassMethod("JsonValue", "JsonValue& append(const JsonValue& in)", asMETHODPR(Json::Value, append, (const Json::Value&), Json::Value&));
//    scriptingEngine_->registerClassMethod("JsonValue", "string toStyledString() const", asMETHOD(Json::Value, toStyledString));
//
//    scriptingEngine_->registerObjectType("JsonParseFromStreamResults", sizeof(JsonParseFromStreamResults), asOBJ_VALUE | asOBJ_APP_CLASS_ALLINTS | asGetTypeTraits<JsonParseFromStreamResults>());
//    scriptingEngine_->registerObjectBehaviour("JsonParseFromStreamResults", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(DefaultConstructor<JsonParseFromStreamResults>), asCALL_CDECL_OBJFIRST);
//    scriptingEngine_->registerObjectBehaviour("JsonParseFromStreamResults", asBEHAVE_DESTRUCT, "void f()", asFUNCTION(DefaultDestructor<JsonParseFromStreamResults>), asCALL_CDECL_OBJFIRST);
//    scriptingEngine_->registerObjectMethod("JsonParseFromStreamResults", "JsonParseFromStreamResults& opAssign(const JsonParseFromStreamResults& in)", asFUNCTION(defaultAssignmentOperator<JsonParseFromStreamResults>), asCALL_CDECL_OBJLAST);
//    scriptingEngine_->registerObjectProperty("JsonParseFromStreamResults", "JsonValue root", asOFFSET(JsonParseFromStreamResults, root));
//    scriptingEngine_->registerObjectProperty("JsonParseFromStreamResults", "string errs", asOFFSET(JsonParseFromStreamResults, errs));
//
//    scriptingEngine_->registerObjectType("JsonCharReaderBuilder", sizeof(Json::CharReaderBuilder), asOBJ_VALUE | asOBJ_APP_CLASS_ALLINTS | asGetTypeTraits<Json::CharReaderBuilder>());
//    scriptingEngine_->registerObjectBehaviour("JsonCharReaderBuilder", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(DefaultConstructor<Json::CharReaderBuilder>), asCALL_CDECL_OBJFIRST);
//    scriptingEngine_->registerObjectBehaviour("JsonCharReaderBuilder", asBEHAVE_DESTRUCT, "void f()", asFUNCTION(DefaultDestructor<Json::CharReaderBuilder>), asCALL_CDECL_OBJFIRST);
//
//    scriptingEngine_->registerGlobalFunction("bool JsonParseFromStream(const JsonCharReaderBuilder& in, unique_ptrIFile& in, JsonParseFromStreamResults& out)", asFUNCTIONPR(JsonParseFromStream, (const Json::CharReaderBuilder&, std::unique_ptr<fs::IFile>&, JsonParseFromStreamResults&), bool), asCALL_CDECL);
//    scriptingEngine_->registerGlobalFunction("bool JsonParseFromStream(const JsonCharReaderBuilder& in, IFile& in, JsonParseFromStreamResults& out)", asFUNCTIONPR(JsonParseFromStream, (const Json::CharReaderBuilder&, fs::IFile&, JsonParseFromStreamResults&), bool), asCALL_CDECL);



//	scriptingEngine_->registerObjectType("Column", sizeof(SQLite::Column), asOBJ_VALUE | asOBJ_APP_CLASS_ALLINTS | asGetTypeTraits<SQLite::Column>());
//	scriptingEngine_->registerObjectBehaviour("Column", asBEHAVE_CONSTRUCT, "void f(const Column& in)", asFUNCTION(CopyConstructor<SQLite::Column>), asCALL_CDECL_OBJLAST);
//	scriptingEngine_->registerObjectBehaviour("Column", asBEHAVE_DESTRUCT, "void f()", asFUNCTION(DefaultDestructor<SQLite::Column>), asCALL_CDECL_OBJFIRST);
//	//auto assignmentOperatorFunctionString = "Column" + std::string("& opAssign(const ") + "Column" + "& in)";
//	//scriptingEngine_->registerObjectMethod("Column", assignmentOperatorFunctionString.c_str(), asFUNCTION(defaultAssignmentOperator<SQLite::Column>), asCALL_CDECL_OBJLAST);
//	scriptingEngine_->registerClassMethod("Column", "int getInt()", asMETHOD(SQLite::Column, getInt));
//	scriptingEngine_->registerObjectMethod("Column", "int opConv()", asFUNCTION((valueCast<SQLite::Column,int>)), asCALL_CDECL_OBJLAST);
//	scriptingEngine_->registerObjectMethod("Column", "int opImplConv()", asFUNCTION((valueCast<SQLite::Column,int>)), asCALL_CDECL_OBJLAST);
//	scriptingEngine_->registerObjectMethod("Column", "string opConv()", asFUNCTION((valueCastString<SQLite::Column,std::string>)), asCALL_CDECL_OBJLAST);
//	scriptingEngine_->registerObjectMethod("Column", "string opImplConv()", asFUNCTION((valueCastString<SQLite::Column,std::string>)), asCALL_CDECL_OBJLAST);
//
//	scriptingEngine_->registerObjectType("Statement", sizeof(SQLite::Statement), asOBJ_VALUE | asOBJ_APP_CLASS_ALLINTS | asGetTypeTraits<SQLite::Statement>());
//	scriptingEngine_->registerObjectBehaviour("Statement", asBEHAVE_CONSTRUCT, "void f(const JsonValue& in, const string& in)", asFUNCTION(jsonvaluebinding::StatementInitConstructor), asCALL_CDECL_OBJLAST);
//	scriptingEngine_->registerObjectBehaviour("Statement", asBEHAVE_DESTRUCT, "void f()", asFUNCTION(DefaultDestructor<SQLite::Statement>), asCALL_CDECL_OBJFIRST);
//	scriptingEngine_->registerClassMethod("Statement", "bool executeStep()", asMETHOD(SQLite::Statement, executeStep));
//	scriptingEngine_->registerClassMethod(
//		"Statement",
//		"Column getColumn(const int)",
//		asMETHODPR(SQLite::Statement, getColumn, (const int), SQLite::Column)
//	);
//	scriptingEngine_->registerClassMethod(
//		"Statement",
//		"void bind(const int, const int)",
//		asMETHODPR(SQLite::Statement, bind, (const int, const int), void)
//	);
}

graphics::gui::ITextEditor* ImGuiColorTextEdit::createTextEditor(graphics::gui::IWindow* window, const std::string text)
{
    auto container = dynamic_cast<graphics::gui::ITextEditorFactory*>(window);

    return container->createTextEditor(text);
}

graphics::gui::ITextEditor* ImGuiColorTextEdit::createTextEditor(graphics::gui::IWindow* window, const uint32 x, const uint32 y, const uint32 width, const uint32 height, const std::string text)
{
    auto container = dynamic_cast<graphics::gui::ITextEditorFactory*>(window);

    return container->createTextEditor(x, y, width, height, text);
}
	
}
};
