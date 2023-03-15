#pragma once

#ifndef FFLOCALPLAYERSDK_H
#define FFLOCALPLAYERSDK_H

/*
callback when create results
#1 int: 0 created success, 1 created fail 
#2 void *fflp handle
#3 void *callback receiver
*/
typedef void(*FFLPCallbackFunc)(int, void *, void *);

_declspec(dllexport) void *fflp_create(char *rtmpUrl, void *winHandle, FFLPCallbackFunc cbFunc, void *cbReceiver);

_declspec(dllexport) void *fflp_resolution(void *fflp, int *width, int *height);

_declspec(dllexport) void fflp_start(void *fflp);

_declspec(dllexport) void fflp_stop(void *fflp);

#endif