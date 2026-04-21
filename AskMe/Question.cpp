#include "Question.h"

        std::string Question::getAnswer() const {
            return answer;
        }

        void Question::setAnswer(std::string _answer) {
            answer = _answer;
        }

        std::string Question::getQuestion() const {
            return question;
        }

        void Question::setQuestion(std::string _question) {
            question = _question;
        }

        int Question::getId() const {
            return id;
        }

        void Question::setId(int _id) {
            id = _id;
        }

        int Question::getParent() const {
            return parent;
        }

        void Question::setParent(int _parent) {
            parent = _parent;
        }

        int Question::getSender() const {
            return sender;
        }

        void Question::setSender(int _sender) {
            sender = _sender;
        }

        int Question::getReceiver() const {
            return receiver;
        }

        void Question::setReceiver(int _receiver) {
            receiver = _receiver;
        }