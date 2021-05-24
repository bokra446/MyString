#pragma once

struct StringRepresentation {
		union {
			struct {
				char* _data;
				unsigned int _size;
			} Long;
			struct {
				char _data[sizeof(Long) - sizeof(char)];
				unsigned char _size;
			} Short;
		} StringType;
    bool isLong = false;
	};