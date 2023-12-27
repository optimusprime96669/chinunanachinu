#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
int identifiercount;
int operatorcount;
int keywordcount;
int integercount;
int hfilecount;
bool isValidDelimiter(char ch){
if (ch == ' ' || ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == ',' || ch == ';' || ch == '>' ||
ch == '<' || ch == '=' || ch == '(' || ch == ')' || ch == '[' || ch == ']' || ch == '{' || ch == '}'){
return(true);
}
return (false);
}
bool preprodir(char *str){
int i;
for(i=0;i<strlen(str);i++){
if(str[i]=='.' && str[i+1]=='h'){
hfilecount++;
return (true);
}
}
return (false);
}
bool isValidOperator(char ch){
if (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '>' || ch == '<' || ch == '='){
operatorcount++;
return (true);
}
return (false);
}
bool isvalidIdentifier(char* str){
if ((str[0] >= 'a' &&str[0]<='z') || (str[0] >= 'A' &&str[0]<='Z') || str[0]=='_'
&& isValidDelimiter(str[0]) == false && str[0]!= '#'){
identifiercount++;
return (true);
}
return (false);
}
bool isValidKeyword(char* str){
if (!strcmp(str, "if") || !strcmp(str, "else") || !strcmp(str, "while") || !strcmp(str, "do") || !strcmp(str, "break")
|| !strcmp(str, "continue") || !strcmp(str, "int") || !strcmp(str, "double") || !strcmp(str, "float")
|| !strcmp(str, "return") || !strcmp(str, "char") || !strcmp(str, "case") || !strcmp(str, "char")
|| !strcmp(str, "sizeof") || !strcmp(str, "long") || !strcmp(str, "short") || !strcmp(str, "typedef")
|| !strcmp(str, "switch") || !strcmp(str, "unsigned") || !strcmp(str, "void") || !strcmp(str, "static")
|| !strcmp(str, "struct") || !strcmp(str, "goto")){

keywordcount++;
return (true);
}
return (false);
}
bool isValidInteger(char* str){
int i, len = strlen(str);
if (len == 0)

return (false);
for (i = 0; i < len; i++) {
if (str[i] != '0' && str[i] != '1' && str[i] != '2'&& str[i] != '3' && str[i] != '4' && str[i] != '5'
&& str[i] != '6' && str[i] != '7' && str[i] != '8' && str[i] != '9' || (str[i] == '-' && i > 0))
return (false);
}
integercount++;
return (true);
}
bool isRealNumber(char* str){
int i, len = strlen(str);
bool hasDecimal = false;
if (len == 0)
return (false);
for (i = 0; i < len; i++) {
if (str[i] != '0' && str[i] != '1' && str[i] != '2' && str[i] != '3' && str[i] != '4' && str[i]!= '5'

&& str[i] != '6' && str[i] != '7' && str[i] != '8' && str[i] != '9' && str[i] != '.' || (str[i] == '-' && i > 0))

return (false);
if (str[i] == '.')
hasDecimal = true;
}
return (hasDecimal);
}
char* subString(char* str, int left, int right){
int i;
char* subStr = (char*)malloc( sizeof(char) * (right - left + 2));
for (i = left; i <= right; i++)
subStr[i - left] = str[i];
subStr[right - left + 1] = '\0';
return (subStr);
}
void detectTokens(char* str){
int left = 0, right = 0;
int length = strlen(str);
while (right <= length && left <= right){
if (isValidDelimiter(str[right]) == false)
right++;
if (isValidDelimiter(str[right]) == true && left == right){
if (isValidOperator(str[right]) == true)
printf("Valid operator : '%c'\n", str[right]);
right++;
left = right;
}

else if (isValidDelimiter(str[right]) == true && left != right || (right == length && left != right)){

char* subStr = subString(str, left, right - 1);
if(preprodir(subStr)==true)
printf("Header file:'%s'\n",subStr);
else if (isValidKeyword(subStr) == true)
printf("Valid keyword : '%s'\n", subStr);
else if (isValidInteger(subStr) == true)
printf("Valid Integer : '%s'\n", subStr);
else if (isRealNumber(subStr) == true)
printf("Real Number : '%s'\n", subStr);
else if (isvalidIdentifier(subStr) == true && isValidDelimiter(str[right - 1]) == false)
printf("Valid Identifier : '%s'\n", subStr);
else if (isvalidIdentifier(subStr) == false && isValidDelimiter(str[right - 1]) == false)
printf("Invalid Identifier : '%s'\n", subStr);
left = right;

}
}
printf("No of identifiers:%d",identifiercount);
printf("\nNo of operators:%d",operatorcount);
printf("\nNo of keywords:%d",keywordcount);
printf("\nNo of integers:%d",integercount);
printf("\nNo of headerfiles:%d",hfilecount);
return;
}
int main(){
char str[100] ;
printf("Enter String:");
scanf("%[^\n]",str);
printf("The Program is:'%s'\n",str);
printf("-----Tokens are-----\n");
detectTokens(str);
return (0);
}