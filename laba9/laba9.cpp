#include <iostream>
using namespace std;

const int hashSize = 1000;

//структура данных хеш-множества
struct HashTree {
    //структура дерева
    struct Tree {
        //узел дерева
        struct Treenode {
            int key = 0;
            Treenode* left = nullptr;
            Treenode* right = nullptr;
        };

        Treenode* root = nullptr;
        int cnt = 0;

        //функция добавления элемента
        void add(int data) {
            if (root == nullptr) {
                root = new Treenode;
                root->key = data;
                cnt++;
            }
            else {
                Treenode* temp = root;
                while (true) {
                    if (data < temp->key) {
                        if (temp->left == nullptr) {
                            temp->left = new Treenode;
                            temp->left->key = data;
                            cnt++;
                            break;
                        }
                        else {
                            temp = temp->left;
                        }
                    }
                    else if (data > temp->key) {
                        if (temp->right == nullptr) {
                            temp->right = new Treenode;
                            temp->right->key = data;
                            cnt++;
                            break;
                        }
                        else {
                            temp = temp->right;
                        }
                    }
                    else {
                        break;
                    }
                }
            }
        }

        //удаление элемента
        void remove(int key) {
            Treenode* parent = nullptr;
            Treenode* temp = root;
            while (temp != nullptr) {
                if (key == temp->key) {
                    break;
                }
                parent = temp;
                if (key < temp->key) {
                    temp = temp->left;
                }
                else if (key > temp->key) {
                    temp = temp->right;
                }
            }
            if (temp == nullptr) {
                return;
            }
            if ((temp->right != nullptr) && (temp->left != nullptr)) {
                parent = temp;
                Treenode* minimum = temp->right;
                while (minimum->left != nullptr) {
                    parent = minimum;
                    minimum = minimum->left;
                }
                temp->key = minimum->key;
                temp = minimum;
            }
            Treenode* child = nullptr;
            if (temp->left != nullptr) {
                child = temp->left;
            }
            else {
                child = temp->right;
            }
            if (temp != root) {
                if (parent->left == temp) {
                    parent->left = child;
                }
                else if (parent->right == temp) {
                    parent->right = child;
                }
            }
            else {
                root = child;
            }
            delete temp;
            cnt--;
        }

        //функция удаления
        void clear(Treenode* temp) {
            if (temp == nullptr) {
                return;
            }
            clear(temp->left);
            clear(temp->right);
            delete temp;
            cnt--;
        }

        //удаление всех элементов
        void clear() {
            clear(root);
            root = nullptr;
        }

        //содержит ли дерево заданный элемент
        bool contains(int data) {
            Treenode* temp = root;
            while (temp != nullptr) {
                if (temp->key == data) {
                    return true;
                }
                else if (temp->key > data) {
                    temp = temp->left;
                }
                else {
                    temp = temp->right;
                }
            }
            return false;
        }

        //количество элементов коллекции
        int count() {
            return cnt;
        }


        void req(int* array, int& index, Treenode* temp) {
            if (temp == nullptr) {
                return;
            }
            req(array, index, temp->left);
            array[index] = temp->key;
            index++;
            req(array, index, temp->right);
        }

        //конвертация в массив
        int* ToArray() {
            int* array = new int[count()];
            int index = 0;
            req(array, index, root);
            return array;
        }
    };

    //массив указателей на связанные списки для хранения слов
    Tree* table[hashSize];
    int cnt = 0;

    //конструктор хеш-множества
    HashTree() {
        cnt = 0;
        for (int i = 0; i < hashSize; i++) {
            table[i] = nullptr;
        }
    }

    //хеш-функция
    int hashFunction(int data) {
        return abs(data) % hashSize;
    }

    //добавление элемента в множество
    void add(int data) {
        if (contains(data)) {
            return;
        }
        int index = hashFunction(data);
        Tree* temp = table[index];
        if (temp == nullptr) {
            table[index] = new Tree;
        }
        table[index]->add(data);
        cnt++;
    }

    //удаление элемента из множества
    void remove(int data) {
        if (!contains(data)) {
            return;
        }
        int index = hashFunction(data);
        if (table[index] == nullptr) {
            return;
        }
        table[index]->remove(data);
        cnt--;
    }

    //удаление всех элементов множества
    void clear() {
        for (int i = 0; i < hashSize; i++) {
            if (table[i] == nullptr) {
                continue;
            }
            table[i]->clear();
        }
        cnt = 0;
    }

    //определяет, содержится ли элемент в множестве
    bool contains(int data) {
        int index = hashFunction(data);
        if (table[index] == nullptr) {
            return false;
        }
        if (table[index]->contains(data)) {
            return true;
        }
        else {
            return false;
        }
    }

    //количество элементов коллекции
    int count() {
        return cnt;
    }

    //конвертация хеш-множества в динамический массив строк
    int* ToArray() {
        int* arr = new int[cnt];
        int j = 0;
        for (int i = 0; i < hashSize; i++) {
            if (table[i] == nullptr) {
                continue;
            }
            int* treeArr = table[i]->ToArray();
            for (int t = 0; t < table[i]->count(); t++) {
                arr[j] = treeArr[t];
                j++;
            }
        }
        return arr;
    }
};

int main()
{
    HashTree hash;
    setlocale(LC_ALL, "Russian");

    cout << "Введите число для:" << endl;
    cout << "1. добавления элементов в множество" << endl << "2. удаления элемента из множества" << endl;
    cout << "3. удаления всех элементов коллекции" << endl << "4. определения, содержится ли указанный элемент в объекте HashSet" << endl;
    cout << "5. подсчета количества элементов в коллекции" << endl << "6. конвертирования хеш-множества в динамический массив строк" << endl;
    cout << "7. завершения работы программы" << endl;


    while (true) {
        int numb;
        int data;
        int* arr;
        cin >> numb;
        switch (numb) {
        case 1:
            cout << "Введите число для добавления: ";
            cin >> data;
            hash.add(data);
            break;
        case 2:
            cout << "Введите число для удаления: ";
            cin >> data;
            hash.remove(data);
            break;
        case 3:
            hash.clear();
            cout << "Хеш-массив пуст!" << endl;
            break;
        case 4:
            cout << "введите число для проверки: ";
            cin >> data;
            if (hash.contains(data)) {
                cout << "это число есть в массиве!" << endl;
            }
            else {
                cout << "этого числа нет в массиве:(" << endl;
            }
            break;
        case 5:
            cout << "количество элементов в коллекции: " << hash.count() << endl;
            break;
        case 6:
            arr = hash.ToArray();
            for (int i = 0; i < hash.count(); i++) {
                cout << arr[i] << " ";
            }
            cout << endl;
            break;
        case 7:
            return 0;
        default:
            cout << "Ошибка!!! Введите корректный номер команды!";
            break;
        }
    }
}