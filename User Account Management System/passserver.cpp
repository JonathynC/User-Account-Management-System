#include "passserver.h"

//PRIVATE FUNCTION
 
string PassServer::encrypt(const string &str) 
{
    char* encode = new char[100];
    char salt[] = "$1$########";
    string product = strcpy(encode, crypt(str.c_str(), salt));
    delete[] encode;
    return product.substr(12);
}

//PUBLIC INTERFACE
 
PassServer::~PassServer() 
{

    server.clear();
}

 
PassServer::PassServer(size_t size) : server(size)
{

}
 
bool PassServer::load(const char *filename) 
{
    return server.load(filename);
}
 
bool PassServer::addUser(pair<string, string> &kv)
{
    kv.second = encrypt(kv.second);
    return server.insert(kv);
}
 
bool PassServer::addUser(pair<string, string> &&kv) 
{
    return addUser(kv);
}
 
bool PassServer::removeUser(const string &k) 
{
    return server.remove(k);
}
 
bool PassServer::changePassword(const pair<string, string> &p, const string &newpassword) 
{
    pair<string,string> temp = p;
    temp.second = encrypt(temp.second);
    if(!server.match(temp))
        return false;
    
    temp.second = encrypt(newpassword);
    server.insert(temp);
    
    return true;
}
 
bool PassServer::find(const string &user) 
{
    return server.contains(user);
}

void PassServer::dump() 
{
    server.dump();
}
 
size_t PassServer::size() 
{
    return server.size();
}
 
bool PassServer::write_to_file(const char *filename) 
{
    return server.write_to_file(filename);
}