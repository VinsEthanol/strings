#include "stringslib.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

size_t str_length(const char *str) {
  if (!str){
    return 0;
  }
  size_t i =0;
  while(str[i]){
    ++i;
  }
  return i;
}

int str_compare(const char *str1, const char *str2) {
  if (!str1){ 
    if (!str2){
      return 0;
    }
    return 1;
  }
  if (!str2){
    return -1;
  }

  size_t i =0;
  while((str1[i] == str2[i]) && (str2[i] != '\0')){
    ++i;
  }

  return str1[i]-str2[i];

}

const char *str_search(const char *needle, const char *haystack) {
  if (needle[0] == '\0'){
    return haystack;
  } 
  size_t needleSize = str_length(needle);
  size_t haystackSize = str_length(haystack);
  if (haystackSize < needleSize){
    return NULL;
  }
  for (size_t i = 0; i < haystackSize; ++i){
    if (haystack[i] == needle[0]){
      for (size_t iNeedle = 0; iNeedle < needleSize; ++iNeedle){
        if (haystack[i+iNeedle] == needle[iNeedle]){
          if (needle[iNeedle+1] == '\0') {
            return haystack+i;
          }
        }else{
          break;
        }
      }
    }
  }
  return NULL;
}


const char *str_search_first_char(char needle, const char *haystack) {
  size_t haystackSize = str_length(haystack);
  for (size_t i = 0; i < haystackSize; ++i){
    if (haystack[i] == needle){
      return haystack+i;
    }
  }
  return NULL;
}

const char *str_search_last_char(char needle, const char *haystack) {
  size_t haystackSize = str_length(haystack);
  for (size_t i = haystackSize; i > 0; --i){
    if (haystack[i] == needle){
      return haystack+i;
    }
  }
  return NULL;
}


size_t str_prefix_accept(const char *str, const char *chars) {
  if (str[0]== '\0'){
    return 0;
  }
  size_t strSize = str_length(str);
  size_t charsize = str_length(chars);
  size_t res = 0;
  size_t j =0;
  for (size_t i = 0; i < strSize; ++i){
    while((res == i) && (j< charsize )){
      if (chars[j]== str[i]){
        ++res;
      }
      ++j;
    }
    j=0;
    if (res==0){
      return res;
    }
  }
  return res;
}

size_t str_prefix_reject(const char *str, const char *chars) {
  if (str[0]== '\0'){
    return 0;
  }
  size_t strSize = str_length(str);
  size_t charsize = str_length(chars);
  size_t res = 0;
  size_t j =0;
  for (size_t i = 0; i < strSize; ++i){
    while((res == i) && (j< charsize )){
      if (chars[j]== str[i]){
        return i;
      }
      ++j;
    }
    j=0;
    ++res;
  }
  return res;
}

int str_to_integer(const char *str) {
  return str_to_integer_ex(str, NULL, 10);
}


int str_to_integer_ex(const char *str, const char **endptr, int base) {
  size_t str_size = str_length(str);
  int nbr =0;
  if (base <= 10){
    for (size_t i=0;str_size; ++i){    
      if ((str[i]>='0')&&(str[i]<base+'0')){ 
        nbr= (nbr*base)+(str[i]-'0');
      }
      else {
        if (endptr){
          *endptr= str + i;
        }
        return nbr;
      }
    }
    return nbr;
  }
  
  for (size_t i=0;str_size; ++i){
    if ((str[i]>='0')&&(str[i]<='9')){
      nbr= (nbr*base)+(str[i]-'0');
    } else if ((str[i]>='A')&&(str[i]<='Z')){
        nbr= nbr*base+(str[i]-'A'+10);
    } else if ((str[i]>='a')&&(str[i]<='z')){
        nbr= nbr*base+(str[i]-'a'+10);
    } else {
      if (endptr){
        *endptr= str + i;
      }
      return nbr;
    }
  }
  return nbr;
}

void str_from_integer(char *dest, size_t size, int n) {
  if (size == 1){
    dest[0]='\0';
  }
  else if (n<10){
    dest[0]= '0'+(char)n;
    dest[1]= '\0';
  }else{
    int *tabOfInt= malloc(sizeof(int)*100);
    if (tabOfInt){
      size_t i=0;
      while (n > 0){
        tabOfInt[i] = n%10;
        ++i;
        n=n/10;
      }
      size_t size_tab=i;
      for (size_t i=0; i < size_tab; ++i){
        if (i<size-1){
          dest[i]= (char)tabOfInt[size_tab-i-1]+'0';
          dest[i+1]='\0';
        }else{
          break;
        }
      }
    }
    free(tabOfInt);
    tabOfInt=NULL;
  }
}

void str_copy(char *dest, size_t size, const char *str) {
  if (size > 1){
    size_t str_size = str_length(str);
    for (size_t i=0;i<=size-1; ++i){
      if (i <= str_size){
        dest[i]= str[i];
      }
    }
  }
  dest[size-1]='\0';
}

char *str_duplicate(const char *str) {
  size_t str_size = str_length(str);
  char *dest = malloc((str_size+1)*sizeof(char));
  
  if (str_size){  
    for (size_t i=0;i<=str_size-1; ++i){
    dest[i]= str[i];
    }
  }

  dest[str_size]='\0';
  return dest;
}

void str_concat_string(char *dest, size_t size, const char *str) {
  size_t dest_size = str_length(dest);
  if (dest_size<size){
    size_t diff= size-dest_size;
    for (size_t i = 0; (i < diff-1) && (str[i]!='\0'); ++i){
      dest[dest_size+i]=str[i];
      dest[dest_size+i+1]='\0';
    }
  }
}

void str_concat_char(char *dest, size_t size, char c) {
  size_t dest_size = str_length(dest);
  if (dest_size+1<size){
    dest[dest_size]= c;
    dest[dest_size+1]='\0';
  }
}

void str_concat_integer(char *dest, size_t size, int n) {
  size_t tempSize= size-1*sizeof(char);
  char *temp= malloc(tempSize);
  if (temp){
    str_from_integer(temp, tempSize, n);
    str_concat_string(dest,size,temp);
  }
  free(temp);
  temp=NULL;
}

void str_concat_array(char *dest, size_t size, const char *args[], char separator) {
  size_t i =0;
  while(args[i]){
    str_concat_char(dest,size,separator);
    str_concat_string(dest,size,args[i]);
    ++i;
  }
}

char *str_join_string(const char *str1, const char *str2, char separator) {
  if (str1){
    if (str2){
      size_t str1Size = str_length(str1);
      size_t str2Size = str_length(str2);
      size_t str3Size = str1Size+str2Size+2;
      char *str3 =malloc(sizeof(char)*str3Size);
      if (str3){
        str3[0]='\0';
        str_concat_string(str3,str3Size,str1);
        str_concat_char(str3,str3Size,separator);
        str_concat_string(str3,str3Size,str2);
      }
      
      return str3;
    }
    size_t str3Size = str_length(str1);
    char *str3 =malloc(sizeof(char)*str3Size);
    if (str3){
    str3[0]='\0';
    str_concat_string(str3,str3Size,str1);
    return str3; 
    }
  }
  if (str2){
    size_t str3Size = str_length(str2)+1;
    char *str3 =malloc(sizeof(char)*str3Size);
    if (str3){
      str3[0]='\0';
      str_concat_string(str3,str3Size,str2);
      return str3;
    }
  }
  char *str3 =malloc(sizeof(char)*1);
  if (str3){
    str3[0]='\0';
  }
  return str3;
}

char *str_join_array(const char *args[], char separator) {
  if (args[0]){
    if (args[1]){
      size_t i =0;
      size_t resSize=0;
      while(args[i]){
        resSize+=str_length(args[i])+1;
        ++i;
      }
      char *res=malloc(sizeof(char)*resSize+1);
      res[0]='\0';
      if(res){
        i =0;
        while(args[i]){
          str_concat_string(res,resSize,args[i]);
          str_concat_char(res,resSize,separator);
          ++i;
        }
      }
      return res;
    }
    size_t args0Size =str_length(args[0])+1;
    char *res=malloc(sizeof(char)*args0Size);
    res[0]='\0';
    str_concat_string(res,args0Size,args[0]);
    return res;
    
  }
  char *res=malloc(sizeof(char));
  res[0]='\0';
  return res;
  
}
