#ifndef _QUESTION_
#define _QUESTION_

#include <iostream>

class Question{
    private:
        std::string answer;
        std::string question;
        int id;
        int parent;
        int sender;
        int receiver;

    public:
        Question() = default;

        std::string getAnswer() const;
        void setAnswer(std::string _answer);
        std::string getQuestion() const;
        void setQuestion(std::string _question);
        int getId() const;
        void setId(int _id);
        int getParent() const;
        void setParent(int _parent);
        int getSender() const;
        void setSender(int _sender);
        int getReceiver() const;
        void setReceiver(int _receiver);
        
        
};

#endif