class singleton{
private:
    singleton(){}
public:
    static singleton& getInstance(){
        static singleton instance;
        return instance;
    }
};
singleton& s1 = singleton::getInstance();

int main()
{
    singleton& s1 = singleton::getInstance();
    return 0;
}