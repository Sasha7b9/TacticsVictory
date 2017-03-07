#pragma once


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class VectorBufferRTS;


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void FUNC_MSG_REQUEST_LANDSCAPE(Connection *connection, MemoryBuffer &in, VectorBufferRTS &out);
void FUNC_MSG_SEND_LANDSCAPE(Connection *connection, MemoryBuffer &in, VectorBufferRTS &out);
void FUNC_MSG_CAMERA_INFO(Connection *connection, MemoryBuffer &in, VectorBufferRTS &out);
void FUNC_MSG_REQUEST_TANKS(Connection *connection, MemoryBuffer &in, VectorBufferRTS &out);
void FUNC_MSG_SEND_TANKS(Connection *connection, MemoryBuffer &in, VectorBufferRTS &out);
void FUNC_MSG_SEND_SCREENSHOT(Connection *connection, MemoryBuffer &in, VectorBufferRTS &out);
