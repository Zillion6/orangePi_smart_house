#ifndef _FACE_H_
#define _FACE_H_

#define WGET_CMD "wget http://127.0.0.1:8080/?action=snapshot -O /home/orangepi/smarthouse/face.jpg"

void face_Init(void);

void face_Finalize(void);

double alicloud_Search_Face(void);

#endif