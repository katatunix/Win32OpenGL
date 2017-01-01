#include <stdio.h>
#include <Windows.h>
#include "gl2.h"

#define GET_PROC_ADDRESS(name) wglGetProcAddress(name)
#define DECL_PFN(func) PFN_##func pfn_##func = NULL
#define STRINGIFY(x) #x
#define GET_PROC(func) if (!pfn_##func) pfn_##func = (PFN_##func)GET_PROC_ADDRESS(STRINGIFY(func))
#define APIENTRYP APIENTRY*

typedef void(APIENTRYP PFN_glClear)(GLbitfield mask); DECL_PFN(glClear);
typedef void(APIENTRYP PFN_glClearColor)(GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha); DECL_PFN(glClearColor);

void glClear(GLbitfield mask) {
	GET_PROC(glClear);
	(*pfn_glClear)(mask);
}

void glClearColor(GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha) {
	GET_PROC(glClearColor);
	(*pfn_glClearColor)(red, green, blue, alpha);
}
