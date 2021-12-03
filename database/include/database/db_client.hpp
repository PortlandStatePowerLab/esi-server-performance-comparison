#ifndef __DB_CLIENT_H__
#define __DB_CLIENT_H__

#include <iostream>
#include <string>
#include <stdlib.h>
#include <mysqlx/xdevapi.h>

class DBClient
{
public:
    DBClient()
    {
        try
        {
            session_ = new mysqlx::Session(
                mysqlx::SessionOption::HOST, "127.0.0.1",
                mysqlx::SessionOption::PORT, 33060,
                mysqlx::SessionOption::USER, "root",
                mysqlx::SessionOption::PWD, "root");
        }
        catch (std::exception &ex)
        {
            std::cout << "MySQL Session: " << ex.what() << std::endl;
            exit (EXIT_FAILURE);
        }
    };

    ~DBClient()
    {
        session_->close();
        delete session_;
    };

    void Insert ()
    {
        std::cout << "MySQL Insert: " << std::endl;
    };

private:
    mysqlx::Session *session_;
};

#endif // __DB_CLIENT_H__