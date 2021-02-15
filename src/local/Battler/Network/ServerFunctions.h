#pragma once



class VectorBufferRTS;



void FUNC_MSG_REQUEST_LANDSCAPE(Connection *, MemoryBuffer &, VectorBufferRTS &);
void FUNC_MSG_CAMERA_INFO(Connection *, MemoryBuffer &, VectorBufferRTS &);
void FUNC_MSG_REQUEST_TANKS(Connection *, MemoryBuffer &, VectorBufferRTS &);
void FUNC_MSG_DELETE_SERVER(Connection *, MemoryBuffer &, VectorBufferRTS &);
void FUNC_MSG_SET_NETWORK_LOSS(Connection *, MemoryBuffer &, VectorBufferRTS &);
void FUNC_MSG_SET_NETWORK_LATENCY(Connection *, MemoryBuffer &, VectorBufferRTS &);
