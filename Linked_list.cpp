

#include <iostream>


class Node {
private:
    int m_num;
    std::string m_data;
    std::shared_ptr<Node> m_prev;
    std::shared_ptr<Node> m_next;

public:
    Node(int NUM, std::string DATA) : m_num{ NUM }, m_data{ DATA }, m_prev{ nullptr }, m_next{ nullptr } {}
    int getIntData() { return m_num; }
    std::string getStringData() { return m_data; }
    std::shared_ptr<Node> getNext() { return m_next; }
    std::shared_ptr<Node> getPrev() { return m_prev; }
    void setNext(std::shared_ptr<Node> NEXT) { m_next = NEXT; }
    void setPrev(std::shared_ptr<Node> PREV) { m_prev = PREV; }

};


class SingleList {
private:
    std::shared_ptr<Node> m_head;
    std::shared_ptr<Node> m_tail;

public:
    SingleList() : m_head{ nullptr }, m_tail{ nullptr } {}
    void addNode(int NUM, std::string DATA);
    void addNodeByNum(int NUM, std::string DATA); //Adds node by its m_num(Int-data). Doesn't work well if it isn't used everytime.
    void printNodes();
    void removeNodeByNum(int NUM); //Gives user the ability to delete individual Nodes with given number
    void printNode(std::shared_ptr<Node> NODE){std::cout << NODE->getIntData() << "\t" << NODE->getStringData() << "\t" << std::endl; }
};

class DoubleList {
private:
    std::shared_ptr<Node> m_head;
    std::shared_ptr<Node> m_tail;

public:
    DoubleList() : m_head{ nullptr }, m_tail{ nullptr } {}
    void addNode(int NUM, std::string DATA);
    void removeNode(int NUM, std::string DATA);
    void printNodes();
};


int main()
{
    /*SingleList List;

    List.addNode(2, "Hello");
    List.addNode(4, "mr.");
    List.addNode(1, "Doe");

    List.printNodes();*/
    //------------------------

    /*SingleList List2;

    List2.addNodeByNum(2, "Hello");
    List2.addNodeByNum(4, "mr.");
    List2.addNodeByNum(1, "Doe");

    List2.printNodes();

    List2.addNodeByNum(2, "Yo");
    List2.addNodeByNum(2, "Hey");
    List2.removeNodeByNum(2);
    List2.printNodes();*/

    //------------------------
    
    DoubleList DList;

    DList.addNode(1, "A");
    DList.addNode(2, "B");
    DList.addNode(3, "C");
    DList.addNode(4, "D");
    DList.addNode(5, "E");

    DList.printNodes();
    DList.removeNode(3, "C");
    DList.printNodes();
}


//SingleList---------------------------------------------------------------------------------------------------
void SingleList::addNode(int NUM, std::string DATA)
{
    std::shared_ptr<Node> newNode = std::make_shared<Node>(NUM, DATA);

    if (m_head == nullptr) {
        m_head = newNode;
        m_tail = newNode;
        return;
    }
    
    m_tail->setNext(newNode);
    m_tail = newNode;

}

void SingleList::addNodeByNum(int NUM, std::string DATA)
{
    std::shared_ptr<Node> newNode = std::make_shared<Node>(NUM, DATA);

    if (m_head == nullptr) {
        m_head = newNode;
        m_tail = newNode;
        return;
    }

    std::shared_ptr<Node> tempNode = m_head;
    std::shared_ptr<Node> lastTempNode = nullptr;

    while (tempNode != nullptr) {
        
        if (newNode->getIntData() <= tempNode->getIntData()) {
            if (tempNode == m_head) {
                newNode->setNext(tempNode);
                m_head = newNode;
                return;
            }
            
            newNode->setNext(tempNode);
            lastTempNode->setNext(newNode);
            return;
        }
        
        if (tempNode == m_tail) {
            tempNode->setNext(newNode);
            m_tail = newNode;
            return;
        }

        lastTempNode = tempNode;
        tempNode = tempNode->getNext();
    }

}

void SingleList::printNodes()
{
    std::shared_ptr<Node> tempNode = m_head;
    int num = 1;
    std::cout << "\nNode\tInt-data\tString-data\t" << std::endl;

    while (tempNode != nullptr) {
        std::cout << num << "\t" << tempNode->getIntData() << "\t\t" << tempNode->getStringData() << "\t" << std::endl;

        tempNode = tempNode->getNext();
        ++num;
    }
}

void SingleList::removeNodeByNum(int NUM)
{

    //SingleList tempList;

    if (m_head == nullptr) {
        std::cout << "List is empty" << std::endl;
        return;
    }
    
    std::shared_ptr<Node> tempNode = m_head;
    std::shared_ptr<Node> lastTempNode = nullptr;
    char choice;

    while (tempNode != nullptr) {
        if (tempNode->getIntData() == NUM) {
            std::cout << "\n----------------------------------------" << std::endl;
            this->printNode(tempNode);
            std::cout << "----------------------------------------" << std::endl;
            std::cout << "Is this the correct node to delete?(y/n)" << std::endl;
            std::cin >> choice;
            if (choice == 'y') {
                if (m_head == tempNode) {
                    m_head = tempNode->getNext();
                    tempNode = m_head;

                }
                else {
                    lastTempNode->setNext((tempNode->getNext()));
                    if (tempNode == m_tail) {
                        m_tail = lastTempNode;
                        return;
                    }
                    tempNode = (tempNode->getNext());
                }
            }
            else if (choice == 'n') {
                std::cout << "Not deleted" << std::endl;
                lastTempNode = tempNode;
                tempNode = tempNode->getNext();
            }
            else {
                std::cout << "Non-valid character" << std::endl;
                return;
            }
        }
        else {
            lastTempNode = tempNode;
            tempNode = tempNode->getNext();
        }


    }

    std::cout << "No Nodes to delete" << std::endl;

}


//~SingleList---------------------------------------------------------------------------------------------------




//DoubleList---------------------------------------------------------------------------------------------------

void DoubleList::addNode(int NUM, std::string DATA)
{
    std::shared_ptr<Node> newNode = std::make_shared<Node>(NUM, DATA);

    if (m_head == nullptr) {
        m_head = newNode;
        m_tail = newNode;
    }

    m_tail->setNext(newNode);
    newNode->setPrev(m_tail);
    m_tail = newNode;

}

void DoubleList::removeNode(int NUM, std::string DATA)
{
    if (m_head == nullptr) {
        std::cout << "List is empty" << std::endl;
        return;
    }


    std::shared_ptr<Node> tempNode = m_head;

    while (tempNode != nullptr) {

        if ((tempNode->getIntData() == NUM) && (tempNode->getStringData() == DATA)) {
            if (tempNode == m_head) {
                m_head = tempNode->getNext();
                (tempNode->getNext())->setPrev(nullptr);
                tempNode->setNext(nullptr);
                return;
            }
            else if (tempNode == m_tail) {
                m_tail = tempNode->getPrev();
                (tempNode->getPrev())->setNext(nullptr);
                tempNode->setPrev(nullptr);
                return;
            }
            else {
                (tempNode->getPrev())->setNext(tempNode->getNext());
                (tempNode->getNext())->setPrev(tempNode->getPrev());
                tempNode->setPrev(nullptr);
                tempNode->setNext(nullptr);
                return;
            }
        }
        tempNode = tempNode->getNext();
    }


}

void DoubleList::printNodes()
{
    std::shared_ptr<Node> tempNode = m_head;
    int num = 1;
    std::cout << "\nNode\tInt-data\tString-data\t" << std::endl;

    while (tempNode != nullptr) {
        std::cout << num << "\t" << tempNode->getIntData() << "\t\t" << tempNode->getStringData() << "\t" << std::endl;

        tempNode = tempNode->getNext();
        ++num;
    }
}
