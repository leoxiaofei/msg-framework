#ifndef IDCREATER_H__
#define IDCREATER_H__


template <typename T>
class IdCreater
{
public:
    IdCreater(const T& data):m_data(data){}
    ~IdCreater(){}

    const T& operator()()
    {
        return ++m_data;
    }
    
    const T& CurID()
    {
        return m_data;
    }

private:
    T m_data;
};

#endif // IDCREATER_H__
