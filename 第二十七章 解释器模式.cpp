#if 0
#include <iostream>
#include <string>
#include <vector>
#include <memory>

class CContext
{
public:
    void SetText(const std::string &text)
    {
        m_text = text;
    }

    void SetText(std::string &&text)
    {
        m_text.swap(std::move(text));
    }

    const std::string &GetText()const
    {
        return m_text;
    }
protected:
private:
    std::string m_text = "";
};

class CExpression
{
public:
    virtual ~CExpression() = default;
    virtual void Interpret(const CContext &context)const = 0;
};

class CTerminalExpression : public CExpression
{
public:
    virtual void Interpret(const CContext &context)const override
    {
        std::cout << "CTerminalExpression" << std::endl;
    }
};

class CNonterminalExpression : public CExpression
{
public:
    virtual void Interpret(const CContext &context)const override
    {
        std::cout << "CNonterminalExpression" << std::endl;
    }
};

int main()
{
    CContext context;
    std::vector<std::shared_ptr<CExpression>> vec;
    vec.push_back(std::make_shared<CTerminalExpression>());
    vec.push_back(std::make_shared<CTerminalExpression>());
    vec.push_back(std::make_shared<CNonterminalExpression>());
    vec.push_back(std::make_shared<CNonterminalExpression>());
    vec.push_back(std::make_shared<CTerminalExpression>());

    for (auto expression : vec)
    {
        expression->Interpret(context);
    }

    return 0;
}
#endif

#include <iostream>
#include <string>
#include <memory>

class CExpression
{
public:
    virtual ~CExpression() = default;
    void Interpret(std::string &context)
    {
        if (context.empty())
        {
            return;
        }

        std::string key = context.substr(0, context.find_first_of(' '));
        context = context.substr(context.find_first_of(' ') + 1);
        std::string value = context.substr(0, context.find_first_of(' '));
        context = context.substr(context.find_first_of(' ') + 1);

        Excucte(key, value);
    }

    virtual void Excucte(const std::string &key, const std::string &value)const = 0;
};

class CNote : public CExpression
{
public:
    virtual void Excucte(const std::string &key, const std::string &value)const override
    {
        std::string note = "";
        if (key == "C")
        {
            note = "1";
        }
        else if (key == "D")
        {
            note = "2";
        }
        else if (key == "E")
        {
            note = "3";
        }
        else if (key == "F")
        {
            note = "4";
        }
        else  if (key == "G")
        {
            note = "5";
        }
        else if (key == "A")
        {
            note = "6";
        }
        else if (key == "B")
        {
            note = "7";
        }
        std::cout << note << " ";
    }

};

class CScale : public CExpression
{
public:
    virtual void Excucte(const std::string &key, const std::string &value)const override
    {
        std::string scale = "";
        switch (std::stoi(value))
        {
        case 1:
            scale = "低音";
            break;
        case 2:
            scale = "中音";
            break;
        case 3:
            scale = "高音";
            break;
        }
        std::cout << scale << " ";
    }
};

class CSpeed : public CExpression
{
public:
    virtual void Excucte(const std::string &key, const std::string &value)const override
    {
        std::string speed = "";

        if (std::stod(value) < 500)
        {
            speed = "快速";
        }
        else if (std::stod(value) > 1000)
        {
            speed = "慢速";
        }
        else
        {
            speed = "中速";
        }

        std::cout << speed << " ";
    }
};

int main()
{

    std::string playText = "T 800 O 2 E 0.5 G 0.5 A 3 ";
    std::shared_ptr<CExpression> se = nullptr;
    while (!playText.empty())
    {
        std::string textTmp = playText.substr(0, 1);
        if (textTmp == "O")
        {
            se = std::make_shared<CScale>();
        }
        else if (textTmp == "C"
            || textTmp == "D"
            || textTmp == "E"
            || textTmp == "F"
            || textTmp == "G"
            || textTmp == "A"
            || textTmp == "B")
        {
            se = std::make_shared<CNote>();
        }
        else if (textTmp == "T")
        {
            se = std::make_shared<CSpeed>();
        }

        if (se != nullptr)
        {
            se->Interpret(playText);
            se = nullptr;
        }
        else
        {
            playText = playText.substr(1);
        }
    }

    std::cout << "\n";
    return 0;
}