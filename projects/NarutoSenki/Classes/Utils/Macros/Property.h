#pragma once

#define PPROP(varType, varName, funName)              \
private:                                              \
	varType varName;                                  \
                                                      \
public:                                               \
	inline varType get##funName() { return varName; } \
	inline void set##funName(varType var) { varName = var; }

#define PROP(varType, varName, funName)               \
protected:                                            \
	varType varName;                                  \
                                                      \
public:                                               \
	inline varType get##funName() { return varName; } \
	inline void set##funName(varType var) { varName = var; }

#define PROP_REF(varType, varName, funName)                  \
protected:                                                   \
	varType varName;                                         \
                                                             \
public:                                                      \
	inline const varType &get##funName() { return varName; } \
	inline void set##funName(const varType &var) { varName = var; }

#define PROP_SREF(varType, varName, funName)           \
protected:                                             \
	varType varName;                                   \
                                                       \
public:                                                \
	inline varType &get##funName() { return varName; } \
	inline void set##funName(const varType &var) { varName = var; }

#define PROP_Vector(varType, varName, funName) PROP_SREF(varType, varName, funName)

// Virtual property

#define VPPROP(varType, varName, funName)                     \
private:                                                      \
	varType varName;                                          \
                                                              \
public:                                                       \
	inline virtual varType get##funName() { return varName; } \
	inline virtual void set##funName(varType var) { varName = var; }

#define VPROP(varType, varName, funName)                      \
protected:                                                    \
	varType varName;                                          \
                                                              \
public:                                                       \
	inline virtual varType get##funName() { return varName; } \
	inline virtual void set##funName(varType var) { varName = var; }

#define VPROP_REF(varType, varName, funName)                         \
protected:                                                           \
	varType varName;                                                 \
                                                                     \
public:                                                              \
	inline virtual const varType &get##funName() { return varName; } \
	inline virtual void set##funName(const varType &var) { varName = var; }
