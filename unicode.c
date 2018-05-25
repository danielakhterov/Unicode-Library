#include "unicode.h"

int u_strtol(char * str){
	for(int i = 0; str[i]; i++){
		if(str[i] >= 'a' && str[i] <= 'z')
			str[i] -= 32;
	}
}
int u_strcmp(char * left, char * right){
	u_strtol(left);
	u_strtol(right);

	int i = 0;

	while(TRUE){
		if(!left[i] && !right[i])
			break;
		if(left[i] > right[i])
			return -1;
		if(left[i] < right[i])
			return 1;
		i++;
	}
	return 0;
}
unsigned u_strc(char * str, int index){
	int pos = 0;
	int cw;
	int length = u_strlen(str);

	for(int i = 0; str[i];){

		if(index >= length)
			return -1;

		cw = u_strmbw(&str[i]);

		if(cw < 0)
			return -1;

		if(pos == index){
			unsigned c = 0;
			for(int j = 0; j < cw; j++){
				c = c << 8;
				c |= str[i + j] & 0xff;
			}
			return c;
		}

		i += cw;
		pos++;
	}
}
int u_strmbw(char * str){
	if(!str[0])
		return 0;

	if((str[0] & 0xC0) == 0x80)
		return -1;

	int i = 0;
	if((str[i] & 0xF8) == 0xF0){
		if(!((str[++i] & 0xC0) == 0x80 && (str[++i] & 0xC0) == 0x80 && (str[++i] & 0xC0) == 0x80)){
			return -1;
		}else{
			return 4;
		}
	}else if((str[i] & 0xF0) == 0xE0){
		if(!((str[++i] & 0xC0) == 0x80 && (str[++i] & 0xC0) == 0x80)){
			return -1;
		}else{
			return 3;
		}
	}else if((str[i] & 0xE0) == 0xC0){
		if(!((str[++i] & 0xC0) == 0x80)){
			return -1;
		}else{
			return 2; } }else if((str[i] & 0x80) == 0){
		return 1;
	}
	return -1;
}
int u_valid(char * str){
	for(int i = 0; str[i]; i++){
		if((str[i] & 0xF8) == 0xF0){
			if(!((str[++i] & 0xC0) == 0x80 && (str[++i] & 0xC0) == 0x80 && (str[++i] & 0xC0) == 0x80)){
				return -1;
			}
		}else if((str[i] & 0xF0) == 0xE0){
			if(!((str[++i] & 0xC0) == 0x80 && (str[++i] & 0xC0) == 0x80)){
				return -1;
			}
		}else if((str[i] & 0xE0) == 0xC0){
			if(!((str[++i] & 0xC0) == 0x80)){
				return -1;
			}
		}else if((str[i] & 0x80) == 1){
			return -1;
		}
	}
	return 0;
}
int u_strlen(char * str){
	int length = 0;
	int cw;
	for(int i = 0; str[i];){
		cw = u_strmbw(&str[i]);
		if(cw < 0)
			return -1;
		else
			i += cw;
		length++;
	}
	return length;
}
