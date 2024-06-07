#include "Utils.h"
#include <windows.h>
#include <iostream>

void SetColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void printGenie() {
    SetColor(11); // Cyan
    std::cout << R"(
                                                  .~)>>
                                                    .~))))>>>
                                                  .~))>>             ___
                                                .~))>>)))>>      .-~))>>
                                              .~)))))>>       .-~))>>)>
                                            .~)))>>))))>>  .-~)>>)>
    )";
    SetColor(13); // Magenta
    std::cout << R"(
                        )                 .~))>>))))>>  .-~)))))>>)>
                     ( )@@*)             //)>))))))  .-~))))>>)>
                   ).@(@@               //))>>))) .-~))>>)))))>>)>
                 (( @.@).              //))))) .-~)>>)))))>>)>
               ))  )@@*.@@ )          //)>))) //))))))>>))))>>)>
            ((  ((@@@.@@             |/))))) //)))))>>)))>>)>
           )) @@*. )@@ )   (\_(\-\b  |))>)) //)))>>)))))))>>)>
         (( @@@(.@(@ .    _/`-`  ~|b |>))) //)>>)))))))>>)>
          )* @@@ )@*     (@) (@)  /\b|))) //))))))>>))))>>
    )";
    SetColor(14); // Yellow
    std::cout << R"(
        (( @. )@( @ .   _/       /  \b)) //))>>)))))>>>_._
         )@@ (@@*)@@.  (6,   6) / ^  \b)//))))))>>)))>>   ~~-.
      ( @jgs@@. @@@.*@_ ~^~^~, /\  ^  \b/)>>))))>>      _.     `,
       ((@@ @@@*.(@@ .   \^^^/' (  ^   \b)))>>        .'         `,
        ((@@).*@@ )@ )    `-'   ((   ^  ~)_          /             `,
          (@@. (@@ ).           (((   ^    `\        |               `.
    )";
    SetColor(10); // Green
    std::cout << R"(
            (*.@*              / ((((        \        \      .         `.
                              /   (((((  \    \    _.-~\     Y,         ;
                             /   / (((((( \    \.-~   _.`" _.-~`,       ;
                            /   /   `(((((()    )    (((((~      `,     ;
                          _/  _/      `"""/   /'                  ;     ;
                      _.-~_.-~           /  /'                _.-~   _.'
                    ((((~~              / /'              _.-~ __.--~
                                       ((((          __.-~ _.-~
                                                   .'   .~~
                                                   :    ,'
                                                   ~~~~~
    )";
    SetColor(11); // Cyan
    std::cout << R"(
          HELLO! I'M NOKO, THE GUESSING MASTER. PLAY MY GAME...IF YOU DARE!!!
    )";
    SetColor(7); // Reset to default color
}
