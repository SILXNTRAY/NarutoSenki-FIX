#pragma once

#define PROP_PTR(varType, varName, funName)            \
protected:                                             \
	RefPtr<varType> varName;                           \
                                                       \
public:                                                \
	inline varType *get##funName() { return varName; } \
	inline void set##funName(varType *var) { varName = var; }

#define PPROP_PTR(varType, varName, funName)           \
private:                                               \
	RefPtr<varType> varName;                           \
                                                       \
public:                                                \
	inline varType *get##funName() { return varName; } \
	inline void set##funName(varType *var) { varName = var; }
