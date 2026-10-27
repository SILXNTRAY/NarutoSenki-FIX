#pragma once

// cocos2d::Value Property

#define PROP_String(varName, funName)                                \
private:                                                             \
	Value varName;                                                   \
                                                                     \
public:                                                              \
	inline std::string get##funName() { return varName.asString(); } \
	inline const Value &get##funName##_Value() { return varName; }   \
	inline void set##funName(const std::string &var) { varName = var; }

#define PROP_Bool(varName, funName)                                \
private:                                                           \
	Value varName;                                                 \
                                                                   \
public:                                                            \
	inline int get##funName() { return varName.asBool(); }         \
	inline const Value &get##funName##_Value() { return varName; } \
	inline void set##funName(int var) { varName = var; }

#define PROP_UInt8(varName, funName)                               \
private:                                                           \
	Value varName;                                                 \
                                                                   \
public:                                                            \
	inline uint8_t get##funName() { return varName.asByte(); }     \
	inline const Value &get##funName##_Value() { return varName; } \
	inline void set##funName(uint8_t var) { varName = var; }

#define PROP_Int(varName, funName)                                 \
private:                                                           \
	Value varName;                                                 \
                                                                   \
public:                                                            \
	inline int get##funName() { return varName.asInt(); }          \
	inline const Value &get##funName##_Value() { return varName; } \
	inline void set##funName(int var) { varName = var; }

#define PROP_UInt(varName, funName)                                    \
private:                                                               \
	Value varName;                                                     \
                                                                       \
public:                                                                \
	inline uint32_t get##funName() { return varName.asUnsignedInt(); } \
	inline const Value &get##funName##_Value() { return varName; }     \
	inline void set##funName(uint32_t var) { varName = var; }

#define PROP_Float(varName, funName)                               \
private:                                                           \
	Value varName;                                                 \
                                                                   \
public:                                                            \
	inline float get##funName() { return varName.asFloat(); }      \
	inline const Value &get##funName##_Value() { return varName; } \
	inline void set##funName(float var) { varName = var; }

#define PROP_Double(varName, funName)                              \
private:                                                           \
	Value varName;                                                 \
                                                                   \
public:                                                            \
	inline double get##funName() { return varName.asDouble(); }    \
	inline const Value &get##funName##_Value() { return varName; } \
	inline void set##funName(double var) { varName = var; }
