#pragma once

// От клиента
const int MSG_REQUEST_LANDSCAPE = 1001;     // Запрос ландшафта
const int MSG_CAMERA_INFO       = 1002;     // Передача инфорамции о камере
const int MSG_REQUEST_TANKS     = 1003;     // Запрос танков

// От сервера
const int MSG_SEND_LANDSCAPE    = 2001;     // Передача ланшафта
const int MSG_SEND_TANKS        = 2002;     // Передача информации о танках для создания
const int MSG_SEND_SCREENSHOT   = 2003;     // Передача информации о всех танках
