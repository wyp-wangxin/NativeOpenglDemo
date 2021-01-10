//
// Created by wyp on 2021/1/9.
//

#ifndef NATIVEOPENGLDEMO_WLANDROIDLOG_H
#define NATIVEOPENGLDEMO_WLANDROIDLOG_H
#include "android/log.h"

#define LOGD(FORMAT, ...) __android_log_print(ANDROID_LOG_DEBUG, "wwxx", FORMAT, ##__VA_ARGS__);
#define LOGE(FORMAT, ...) __android_log_print(ANDROID_LOG_ERROR, "wwxx", FORMAT, ##__VA_ARGS__);

#endif //NATIVEOPENGLDEMO_WLANDROIDLOG_H
