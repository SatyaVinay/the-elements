/*
 * app-android.c
 * -----------------------------
 * Contains the entire API for our JNI code. Any
 * access to the native code from Java will be made
 * using these accessible functions.
 */

#include <jni.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
//#include <android/log.h>

//Include the global variables
#include "app.h"
//Include the global macros
#include "macros.h"
//Include the initializing function
#include "setup.h"
//Include the element characteristics file
#include "elementproperties.h"
//Include the collisions data file
#include "collisions.h"
//Include the saving and loading functions
#include "saveload.h"
//Include the server access functions
#include "server.h"
//Include the rendering functions
#include "gl.h"

void Java_sand_wallpaper_opengl_DemoRenderer_nativeInit(JNIEnv* env) //Initialize graphics
{
	//__android_log_write(ANDROID_LOG_INFO, "DemoActivity", "8");
	importGLInit();
	appInit();
	gAppAlive = 1;
	//__android_log_write(ANDROID_LOG_INFO, "DemoActivity", "4");
}

void Java_sand_wallpaper_opengl_DemoRenderer_nativeResize(JNIEnv* env, jobject thiz, jint w, jint h)
{
	if (screensize == 0) //this didn't work before becuase tej used = instead of == (green girdle)
	{
		maxx = w / 2;
		maxy = h / 2;
	}
	else
	{
		maxx = w;
		maxy = h;
	}
	appInit();
}

void Java_sand_wallpaper_opengl_DemoRenderer_nativeDone(JNIEnv* env)
{
	appDeinit();
	importGLDeinit();
}

//these two get the gravity from the java code
void Java_sand_wallpaper_opengl_DemoActivity_sendyg(JNIEnv* env, jobject thiz, jfloat ygrav)
{
	gravy = ygrav;
}
void Java_sand_wallpaper_opengl_DemoActivity_sendxg(JNIEnv* env, jobject thiz, jfloat xgrav)
{
	gravx = -xgrav;
}
void Java_sand_wallpaper_opengl_DemoActivity_quickload(JNIEnv* env)
{
	loader(1);
}
void Java_sand_wallpaper_opengl_DemoActivity_quicksave(JNIEnv* env)
{
	saver(1);
}

/* Call to render the next GL frame */
void Java_sand_wallpaper_opengl_DemoRenderer_nativeRender(JNIEnv* env)
{
	appRender();
}

void Java_sand_wallpaper_opengl_DemoActivity_setup(JNIEnv* env, jobject thiz)
{
	rsetup();
}

void Java_sand_wallpaper_opengl_DemoActivity_jPause(JNIEnv* env, jobject thiz)
{
	play = 0;
}
void Java_sand_wallpaper_opengl_DemoActivity_Play(JNIEnv* env, jobject thiz)
{
	play = 1;
}

void Java_sand_wallpaper_opengl_DemoActivity_setBackgroundColor(JNIEnv* env, jobject thiz, jint colorcode)
{
	if (colorcode == 0)
	{
		red[3] = 0; //3 is eraser
		blue[3] = 0;
		green[3] = 0;
		//__android_log_write(ANDROID_LOG_INFO, "DemoActivity", "color");
		rsetup();
	}
	else if (colorcode == 1)
	{
		red[3] = 255;
		blue[3] = 255;
		green[3] = 255;
		//__android_log_write(ANDROID_LOG_INFO, "DemoActivity", "color");
		rsetup();
	}
	loader(1);
}
void Java_sand_wallpaper_opengl_DemoActivity_setexplosiveness(JNIEnv* env, jobject thiz, jint explosiveness)
{
	exploness[22] = explosiveness;
}
void Java_sand_wallpaper_opengl_DemoActivity_setred(JNIEnv* env, jobject thiz, jint redness)
{
	red[22] = redness;
}
void Java_sand_wallpaper_opengl_DemoActivity_setgreen(JNIEnv* env, jobject thiz, jint greenness)
{
	green[22] = greenness;
}
void Java_sand_wallpaper_opengl_DemoActivity_setblue(JNIEnv* env, jobject thiz, jint blueness)
{
	blue[22] = blueness;
}

void Java_sand_wallpaper_opengl_DemoActivity_setdensity(JNIEnv* env, jobject thiz, jint jdensity)
{
	density[22] = jdensity;
}
void Java_sand_wallpaper_opengl_DemoActivity_setFlip(JNIEnv* env, jobject thiz, jint jflipped)
{
	flipped = jflipped;
}
void Java_sand_wallpaper_opengl_DemoActivity_setcollision(JNIEnv* env, jobject thiz, jint custnum, jint elementnumb, jint colspot, jint colnum)
{
	if (custnum == 1)
	{
		collision[22][colspot] = colnum;
		colliseelement1[colspot] = elementnumb;
		collision[colspot][22] = colnum;
	}
	else
	{
		collision[22][colspot] = colnum;
		colliseelement1[colspot] = elementnumb;
		collision[colspot][22] = colnum;
	}
	int counter124;
	char foundfire = 0;
	for (counter124 = 0; counter124 < TElements; counter124++)
	{
		if (collision[22][counter124] == 6)
		{
			foundfire = 1;
		}
	}
	if (foundfire == 0)
	{
		fireburn[22] = 0;
	}
	else
	{
		fireburn[22] = 1;
	}
}

void Java_sand_wallpaper_opengl_DemoActivity_fd(JNIEnv* env, jobject thiz, jint fstate)
{
	//setting finger up or down from onTouch

	fd = fstate;
	if (fd == 1)
	{
		xm = -1;
	}
	return;
}
void Java_sand_wallpaper_opengl_DemoActivity_mp(JNIEnv* env, jobject thiz, jint jxm, jint jym)
{
	//setting the mouse position when given stuff from jdk
	if (xm != -1)
	{
		lmx = xm;
		lmy = ym;

		int xc = jxm - lmx; //change in x (delta x)
		int yc = jym - lmy; //change in y (delta y)


		int dist = sqrt(xc * xc + yc * yc); //distance between two points


		if (dist > 0 && celement != 16) //if it's not the same place and 
		{
			int xd = xc / dist; // change divided by distance
			int yd = yc / dist;
			int counter;
			int oldplay = play;
			play = 0;
			for (counter = 0; counter <= dist; counter++)
			{
				ym = yd * counter + lmy;
				xm = xd * counter + lmx;
				UpdateView();
			}
			play = oldplay;
		}
	}
	xm = jxm;
	ym = jym;
	return;
}
void Java_sand_wallpaper_opengl_DemoActivity_clearquicksave(JNIEnv* env, jobject thiz)
{
	removeQuicksave();
	return;
}
void Java_sand_wallpaper_opengl_DemoActivity_setelement(JNIEnv* env, jobject thiz, jint jelement)
{
	celement = jelement;
	return;
}
int Java_sand_wallpaper_opengl_DemoActivity_getelement(JNIEnv* env, jobject thiz)
{
	return celement;
}
void Java_sand_wallpaper_opengl_DemoActivity_setBrushSize(JNIEnv* env, jobject thiz, jint jsize)
{
	size = jsize;
	return;
}
void Java_sand_wallpaper_opengl_DemoActivity_setAccelOnOff(JNIEnv* env, jobject thiz, jint state)
{
	accelcon = state;
	return;
}
void Java_sand_wallpaper_opengl_DemoActivity_togglesize(JNIEnv* env, jobject thiz)
{
	if (screensize == 0) //not zoomed in, *2 to zoom out
	{
		screensize = 1;
		maxx = maxx * 2;
		maxy = maxy * 2;
	}
	else
	{
		screensize = 0; //zoomed in
		maxx = maxx / 2;
		maxy = maxy / 2;
	}
}
int Java_sand_wallpaper_opengl_DemoActivity_save(JNIEnv* env, jobject thiz)
{
	return saver(0); //Do a normal save
}

int Java_sand_wallpaper_opengl_DemoActivity_load(JNIEnv* env, jobject thiz)
{
	return loader(0); // call the load function, normal load
}

void Java_sand_wallpaper_opengl_DemoActivity_loaddemo(JNIEnv* env, jobject thiz)
{
	loadDemoFile();
}
void Java_sand_wallpaper_opengl_DemoActivity_loadcustom(JNIEnv* env, jobject thiz)
{
	loadCustomFile();
}
void Java_sand_wallpaper_opengl_DemoActivity_savecustom(JNIEnv* env, jobject thiz)
{
	saveCustomFile();
}

void Java_sand_wallpaper_opengl_DemoActivity_setPassword(JNIEnv *env, jobject thiz, jbyteArray minut)
{
	int i; //Counter variable

	//Get the array length of the password
	jsize len  = (*env)->GetArrayLength(env,minut);
	//Create a byte array with the size of the array in the byteArray object
	jbyte* minut1 = (jbyte *)malloc(len * sizeof(jbyte));

	//Extract the byteArray object to a byte array
	(*env)->GetByteArrayRegion(env,minut,0,len,minut1);

	//Copy the byte array over into the password
	for(i = 0; i < len; i++)
	{
		password[i] = minut1[i];
	}
	//Add the null byte
	password[len] = 0;
	//Set the length variable
	passlength = len;

	//Free the created byte array
	free(minut1);
}

void Java_sand_wallpaper_opengl_DemoActivity_setUserName(JNIEnv *env, jobject thiz, jbyteArray minut)
{
	int i; //Counter variable

	//Get the array length of the username
	jsize len  = (*env)->GetArrayLength(env,minut);
	//Create a byte array with the size of the array in the byteArray object
	jbyte* minut1 = (jbyte *)malloc(len * sizeof(jbyte));

	//Extract the byteArray object to a byte array
	(*env)->GetByteArrayRegion(env,minut,0,len,minut1);

	//Copy the byte array over into the username
	for(i = 0; i < len; i++)
	{
		username[i] = minut1[i];
	}
	//Add the null byte
	username[len] = 0;
	//Set the length variable
	userlength = len;

	//Free the created byte array
	free(minut1);
}

int Java_sand_wallpaper_opengl_DemoActivity_login(JNIEnv *env, jobject thiz)
{
	buildbuffer(3);
	if(!sendbuffer())
	{
		return -1;
	}

	return 0;
}
int Java_sand_wallpaper_opengl_DemoActivity_register(JNIEnv *env, jobject thiz)
{
	buildbuffer(2);
	if(!sendbuffer())
	{
		return -1;
	}


	return 0;
}

char* Java_sand_wallpaper_opengl_DemoActivity_viewerr (JNIEnv *env, jobject thiz)
{
	return error;
}
