#include <iostream>
#include <string.h>
#include <vector>
struct token{
    std::string value;
    int type;
};
enum var_types{
    NONE_VAR_TYPE,
    INT_VAR_TYPE
};
enum TOKEN_TYPE{
    VAR_TYPE_INT,
    STRING,
    NAME,
    EQUAL_SIGN,
    SEMI_COLON,
    NUMBER,
    UNKOWN,
};
class Variable{
    public:
        int type = NONE_VAR_TYPE;
        std::string name;
        int int_value;
        std::string string_value;
};
struct variables{
    std::vector<Variable>var;
};

variables vars;


class Lexer{
    private:
        int GetTokeNum(std::string);

    public:
        std::vector<token> tokenize(std::string);
};
int Lexer::GetTokeNum(std::string tok){
    if (strcmp(tok.c_str(), "int") == 0){
        return VAR_TYPE_INT;
    }
    else{
        return UNKOWN;
    }
}

std::vector<token> Lexer::tokenize(std::string code){
    std::vector<token> tokens;
    int last_value_end=0;
    bool skipped =false;
    for (int x = 0;x < code.length();x++ ){
        if (code[x] == ';'){
            tokens.push_back(token());
            tokens[tokens.size()-1].value.append(1, ';');
        }
        else if (code[x] == '\n'){
            continue;
        }
        else if (code[x] == '='){
            if (x-last_value_end == 1 && code[last_value_end+1] == ' '){
                tokens.push_back(token());
                tokens[tokens.size()-1].value.append(1, '=');
            }
            else{
                tokens.push_back(token());
                for (int y = 0; y < x-last_value_end; y++){
                    if (last_value_end != 0 && y == 0)
                        continue;
                    tokens[tokens.size()-1].value.append(1, code[last_value_end+y]); 
                }
                last_value_end = x;
                tokens.push_back(token());
                tokens[tokens.size()-1].value.append(1, '=');
            }
        }
        else if (code[x] == ' '){
            if (x-last_value_end == 1 && code[last_value_end+1] == ' ')
                last_value_end = x;
            else{
                tokens.push_back(token());
                for (int y = 0; y < x-last_value_end; y++){
                    if (last_value_end != 0 && y == 0)
                        continue;
                    tokens[tokens.size()-1].value.append(1, code[last_value_end+y]); 
                }
                tokens[tokens.size()-1].type = GetTokeNum(tokens[tokens.size()-1].value);
                last_value_end = x;
            }
        }
        else if (code[x] <= '9' || code[x] <= '0'){
            if ( tokens[tokens.size()-1].value.at(0) <= '9' || tokens[tokens.size()-1].value.at(0) <= '0'){
                tokens[tokens.size()-1].value.append(1,code[x]);
            }
            else{
                tokens.push_back(token());
                tokens[tokens.size()-1].value.append(1, code[x]);
            }
        }
    }
    return tokens;
}



class Parser{
    public:
        void parser(std::vector<token> tokens){
            for (int k = 0; k < tokens.size(); k++){
                if (k == 0 && tokens[k].type == VAR_TYPE_INT){
                    vars.var.push_back(Variable());
                    vars.var[vars.var.size()-1].type=INT_VAR_TYPE;
                    vars.var[vars.var.size()-1].name=tokens[k+1].value;
                    std::cout << vars.var[vars.var.size()-1].name << "\n";
                }
                else if (strcmp(tokens[k].value.c_str(), "=") == 0){
                    vars.var[vars.var.size()-1].int_value = atoi( tokens[k+1].value.c_str() );
                    std::cout << vars.var[vars.var.size()-1].int_value << "\n";
                }
            }

        }
};
int main() {
    Lexer lexer;
    Parser parser;
    std::string code = "int hello=                   091;\n";
    std::vector<token> tokens = lexer.tokenize(code);
    parser.parser(tokens);    
}