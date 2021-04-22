// 2021/04/07 20:38:43 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once


// Обрабатываемые мастер-сервером запросы
#define MSG_NTW_PING                "ping"                  // запрос пинга
#define MSG_NTW_INFO_LIVINGROOM     "info_livingroom"       // Этим сообщением гостиная сообщает мастер-серверу о
                                                            // своём состоянии
#define MSG_NTW_SET_NAME_LIVINGROOM "set_name_livingrom"    // Установка имени гостиной
                                                            // Запрос смещения порта гостевой комнаты относительно

#define MSG_NTW_GET                 "get"
#define MSG_NTW_GET_PORT_LIVINGROOM_BROADCAST_UDP           \
                                            MSG_NTW_GET " port livingroom_broadcast_udp"   // порта мастер-сервера
