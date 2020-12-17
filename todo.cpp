#include<vector>
#include<fstream>
#include<ctime>
#include <iostream>

using namespace std;

int count_lines(string file_name)
{   
    int count = 0;
    string line;
    fstream file(file_name, ios::in);
    while(getline(file, line))
        count++;
    file.close();
    return count;
}

int main(int argc, char* argv[])
{
    if(argc > 1)
    {
        string s = argv[1];
        if(s == "report")
        {
            int pending, completed;
            pending = count_lines("todo.txt");
            completed = count_lines("done.txt");
            time_t now = time(0);
            tm *data = localtime(&now);
            cout<<data->tm_mday<<"/"<<data->tm_mon<<"/"<<data->tm_year<<"  ";
            cout<<"Pending : "<<pending<<"  "<<"Completed : "<<completed<<endl;
        }
        else if(s == "help")
        {
            cout<<"todo add TODO-ITEM \t # Add a new todo"<<endl;
            cout<<"todo ls              \t # Show remaining todos"<<endl;
            cout<<"todo del NUMBER      \t # Delete a todo"<<endl;
            cout<<"todo done NUMBER     \t # Complete a todo"<<endl;
            cout<<"todo help            \t # Show usage"<<endl;
            cout<<"todo report          \t # Statistics"<<endl;
        }
        else if(s == "ls")
        {
            string text;
            fstream file;
            int i=1;
            file.open("todo.txt", ios::in);
            if(!file)
                cout<<"File does not exist"<<endl;
            else
            {
                while(getline(file, text))
                {
                    cout<<i<<". "<<text<<endl;
                    i++;
                }  
            }
            cout<<endl;
            file.close();
        }
        else if(s == "add")
        {
            string item = argv[2];
            fstream file("todo.txt", ios::app);
            file<<item + "\n";
            file.close();
            cout<<"added todo : "<<item<<endl;
        }
        else if(s == "del")
        {
            string g;
            string no = argv[2];
            string data, line;
            int line_no = stoi(no);
            fstream file("todo.txt", ios::in | ios::out);
            // fetch the line @ line_no -
            int i=1;
            while(getline(file, data) && i<line_no)
            {   
                i++;
            }
            g = data;
            file.close();
            // creating temp file and then rename it -
            ifstream sup;
            sup.open("todo.txt");
            ofstream temp;
            temp.open("temp.txt");
            while(getline(sup,line))
            {
                if(line != g)
                    temp << line<< endl;
            }
            temp.close();
            sup.close();
            cout<<"Deleted todo : "<<g<<endl;
            remove("todo.txt");
            rename("temp.txt", "todo.txt");
        }
        else if(s == "done")
        {
            // fetch the line @ line_no -
            string g;
            string no = argv[2];
            string data, line;
            int line_no = stoi(no);
            fstream file("todo.txt", ios::in | ios::out);
            int i=1;
            while(getline(file, data) && i<line_no)
            {   
                i++;
            }
            g = data;
            file.close();
            // append that line into done.txt -
            fstream f("done.txt", ios::app);
            f<<g + "\n";
            f.close();
            // creating temp file and then rename it -
            ifstream sup;
            sup.open("todo.txt");
            ofstream temp;
            temp.open("temp.txt");
            while(getline(sup,line))
            {
                if(line != g)
                    temp << line<< endl;
            }
            temp.close();
            sup.close();
            // cout<<"Deleted todo : "<<g<<endl;
            remove("todo.txt");
            rename("temp.txt", "todo.txt");
            cout<<"Marked todo "<<line_no<<" as done"<<endl;
        }
    }
    else
    {
        cout<<"todo add 'todo item' \t # Add a new todo"<<endl;
        cout<<"todo ls              \t # Show remaining todos"<<endl;
        cout<<"todo del NUMBER      \t # Delete a todo"<<endl;
        cout<<"todo done NUMBER     \t # Complete a todo"<<endl;
        cout<<"todo help            \t # Show usage"<<endl;
        cout<<"todo report          \t # Statistics"<<endl;
    }
    
    return 0;
}
