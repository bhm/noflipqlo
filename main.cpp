/*
 * Copyright (c) 2010 Kuźniarski Jacek <JKuzniarski@gmail.com>
 *
 * Permission to use, copy, modify, and distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */
 
#ifdef __cplusplus
    #include <cstdlib>
#else
    #include <stdlib.h>
#endif
#ifdef __APPLE__
#include <SDL/SDL.h>
#else
#include "SDL.h"
#endif
#include "SDL_ttf.h"
#include "SDL_syswm.h"
//#include <iostream>
#include <time.h>
#include <string.h>
#include <string>
#include <sstream>
#include <X11/Xlib.h>
#include "SDL_rotozoom.h"
using namespace std;
int past_m=NULL;
bool twentyfourh = true;
bool fullscreen  = false;
SDL_Surface *screen;
SDL_Surface *flipclock;
SDL_Surface *s_hour;
SDL_Surface *s_min;
SDL_Surface *s_mode;
SDL_Surface *background;
TTF_Font *font_time = NULL;
TTF_Font *font_mode = NULL;
SDL_Color clrWhite = {176,176,176};

Uint32 checkEmit(Uint32 interval, void *param)
{
        time_t rawtime;
        struct tm * time_i;
        time(&rawtime);
        time_i = localtime(&rawtime);

        if ( time_i->tm_min != past_m)
        {
            SDL_Event e;

            e.type = SDL_USEREVENT;
            e.user.code = 0;
            e.user.data1 = NULL;
            e.user.data2 = NULL;
            SDL_PushEvent(&e);

            //std::cout << "Time is: " << time_i->tm_hour << ":" << time_i->tm_min << std::endl;
            printf("Time is: %d : %d\n", time_i->tm_hour, time_i->tm_min);
            past_m = time_i->tm_min;
        }
        return (interval);
}
int initSDL()
{
      // initialize SDL video and SDL INIT TIMER
    if ( SDL_Init( SDL_INIT_VIDEO|SDL_INIT_TIMER ) < 0 )
    {
        printf( "Unable to init SDL: %s\n", SDL_GetError() );
        return 1;
    }
    return 0;
}

int initRescouces()
{
    background = SDL_LoadBMP("/usr/share/images/back.bmp");
    if (!background)
    {
            printf("Unable to load bitmap: %s\n", SDL_GetError());
            return 1;

    }
    font_time = TTF_OpenFont( "/usr/share/fonts/truetype/ttf-droid/DroidSans-Bold.ttf", 240 );
    font_mode = TTF_OpenFont( "/usr/share/fonts/truetype/ttf-droid/DroidSans-Bold.ttf", 30 );
    if(!font_time)
    {
        printf("TTF_OpenFont: %s\n", TTF_GetError());
    }
    SDL_AddTimer(500, checkEmit, NULL);
    return 0;
}

/*
    Goes to shitter.
*/
//int drawBG(){
//        SDL_Rect dstrect;
//        dstrect.x = (screen->w - background->w) / 2;
//        dstrect.y = (screen->h - background->h) / 2;
//        SDL_BlitSurface(background, 0, screen, &dstrect);
//        SDL_Flip(screen);
//        return 0;
//}

/*
    Passed variables went to shitter
        a) XWindowAttribute height and width are unsigned int, conversion sucked donkey balls
        b) we get surfaces globaly so far anyway.
*/
int drawTime()
{
    /*
    Shittiest way to do this. Too much I/O.
    */
    flipclock = SDL_LoadBMP("/usr/share/images/back.bmp");
    if (!flipclock)
    {
            printf("Unable to load bitmap: %s\n", SDL_GetError());
            return 1;

    }


    time_t rawtime;
    struct tm * _time;
    time(&rawtime);
    _time = localtime(&rawtime);

    string curHour;
    string curMin;
    stringstream convH;
    stringstream convM;
//    int i_curHour =23;
//    int i_curMin = 9;
    int i_curHour = _time->tm_hour;
    int i_curMin = _time->tm_min;
    convM << i_curMin;

    SDL_Rect coord_H;
    coord_H.x = 23;
    coord_H.y = 15;
    SDL_Rect coord_M;
    coord_M.x = 320;
    coord_M.y =  coord_H.y;

    if ( i_curMin <=9)
    {
        curMin += "0";
        curMin += convM.str();
    }
    else
    {
        curMin = convM.str();
    }
    if(!twentyfourh)
    {
        string time_mode;
        SDL_Rect coord_mode;

        if ((i_curHour) <= 11)
        {
            time_mode = "AM";
            coord_mode.x = 15;
            coord_mode.y = 60;
        }
        if ( (i_curHour) >=12)
        {
            coord_mode.x = 15;
            coord_mode.y = 210;
            time_mode = "PM";
            i_curHour -= 12;
        }
         if ((i_curHour) == 12 || (i_curHour) == 0)
        {
            time_mode = "";
        }

        if ( (i_curHour)<=9)
        {
              convH << i_curHour;
              coord_H.x += 50;
              curHour += convH.str();
         }
         else
         {
              convH << i_curHour;
              curHour = convH.str();
         }
        s_mode = TTF_RenderText_Blended(font_mode, time_mode.c_str(), clrWhite);
        SDL_BlitSurface(s_mode, 0, flipclock, &coord_mode);
    }
    else
    {
        if ( i_curHour<=9)
        {
                convH << i_curHour;

                curHour += "0";
                curHour += convH.str();
        }
        else
        {
            convH << i_curHour;
            curHour = convH.str();
        }
    }

    s_hour = TTF_RenderText_Blended(font_time, curHour.c_str(), clrWhite);
    s_min = TTF_RenderText_Blended(font_time, curMin.c_str(), clrWhite);

    SDL_Rect dstrect;

    // Strike through line
    SDL_Rect div_line;
    div_line.h = 3;
    div_line.w = screen->w;
    div_line.y = (screen->h)/2;
    div_line.x = 0;

    SDL_BlitSurface(s_hour, 0, flipclock, &coord_H);
    SDL_BlitSurface(s_min, 0, flipclock, &coord_M);

    double ratio = screen->h / 480.0;
    flipclock = zoomSurface(flipclock, ratio, ratio, SMOOTHING_ON);


    dstrect.x = (screen->w - flipclock->w) / 2;
    dstrect.y = (screen->h - flipclock->h) / 2;
    SDL_BlitSurface(flipclock, 0, screen, &dstrect);
    SDL_FillRect(screen, &div_line, SDL_MapRGB(screen->format, 0,0,0));
    SDL_Flip(screen);
    return 0;
}


int main ( int argc, char** argv )
{
    char *wid_env;
    static char sdlwid[100];
    Uint32 wid = 0;
    Display *dpy;
    XWindowAttributes winattr;
    winattr.height = 0;
    winattr.width =0;

    /* If no window argument, check environment */
    if (wid == 0) {
        if ((wid_env = getenv("XSCREENSAVER_WINDOW")) != NULL ) {
            wid = strtol(wid_env, (char **) NULL, 0); /* Base 0 autodetects hex/dec */
        }
    }

    /* Get win attrs if we've been given a window, otherwise we'll use our own */
    if (wid != 0 ) {
        if ((dpy = XOpenDisplay(NULL)) != NULL) { /* Use the default display */
            XGetWindowAttributes(dpy, (Window) wid, &winattr);
            XCloseDisplay(dpy);
            snprintf(sdlwid, 100, "SDL_WINDOWID=0x%X", wid);
            putenv(sdlwid); /* Tell SDL to use this window */
        }
    }

    initSDL();
    TTF_Init();
    initRescouces();
    SDL_ShowCursor( SDL_DISABLE );

    // Thou shalt GTFO when I say so
    atexit(SDL_Quit);
    atexit(TTF_Quit);

    for(int i=1;i<argc;i++)
    {
        if(strcmp("--help",argv[i])==0)
        {
            printf("Usage: [OPTION...]\nOptions:\n  -root  Fullscreen\n  --help Display this\n  -ampm   Turn off 24 h system\n");
            return 0;
        }
        else if (strcmp("-root",argv[i])==0 || strcmp("--root", argv[i]) == 0)
        {
            fullscreen=true;
        }
        else if (strcmp("-ampm",argv[i])==0)
        {
             twentyfourh=false;
        }
    }

    // Let there be ground
    if(fullscreen)
    {
        screen = SDL_SetVideoMode(winattr.width, winattr.height, 32,
                                           SDL_HWSURFACE|SDL_DOUBLEBUF|SDL_FULLSCREEN);

    }
    else
    {
        screen = SDL_SetVideoMode(640, 480, 32,
                                           SDL_HWSURFACE|SDL_DOUBLEBUF);
    }

    if ( !screen )
    {
        printf("Unable to set video mode: %s\n", SDL_GetError());
        return 1;
    }

    // program main loop
    bool done = false;
    while (!done)
    {
        // message processing loop
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            // check for messages
            switch (event.type)
            {
            case SDL_USEREVENT:
                    drawTime();
                break;
            // exit if the window is closed
            case SDL_QUIT:
                done = true;
                break;
                // check for keypresses
            case SDL_KEYDOWN:
                {
                    // exit if ESCAPE is pressed
                    if (event.key.keysym.sym == SDLK_ESCAPE)
                        done = true;
                    break;
                }
            } // end switch
        } // end of message processing

        // Lights out show on.
        SDL_FillRect(screen, 0, SDL_MapRGB(screen->format, 0, 0, 0));
        //SDL_Flip(screen);
    } // end main loop

    // There I say, get the fuck out.
    SDL_FreeSurface(background);
    SDL_FreeSurface(s_hour);
    SDL_FreeSurface(s_min);
    SDL_FreeSurface(flipclock);
    SDL_FreeSurface(screen);
    SDL_FreeSurface(s_mode);
    TTF_CloseFont(font_time);
    TTF_CloseFont(font_mode);

    // all is well ;)
    printf("Exited cleanly\n");
    return 0;
}
