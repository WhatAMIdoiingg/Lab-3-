#include <iostream>
#include <conio.h>
#include <queue>
#include <vector>
#include<stdlib.h>
#include <chrono>
#include <random>
#pragma comment(linker, "/STACK:1000000000000")
using namespace std;
using namespace std::chrono;
const static bool RED = 0;
const static bool BLACK = 1;


class Binary_Tree {

    struct node
    {
        int key;//значение узла
        struct node* Left_child = nullptr, * Right_child = nullptr, * Parent = nullptr;//левый и правый потомок, родитель
        node(int key) {
            this->key = key;
        }
    } *root = nullptr;



    struct node* find(int key, node* root)//функция поиска 
    {
        while (root != NULL and root->key != key)// пока узел существует и ключи текущего и искомого не совпадают 
        {
            if (key < root->key)//менше - идем в левое поддерево
            {
                root = root->Left_child;
            }
            else// больше - идем в провое поддерево
            {
                root = root->Right_child;
            }
        }
        return root;
    }

    struct node* Tree_minimum(node* root)
    {
        while (root->Left_child != NULL)
        {
            root = root->Left_child;
        }
        return root;
    }
    struct node* Tree_maximum(node* root)
    {
        while (root->Right_child != NULL)
        {
            root = root->Right_child;
        }
        return root;
    }

    struct node* Tree_Successor(node* Node)//как у доски
    {
        if (Node->Right_child != NULL)
        {
            Node = Node->Right_child;
            while (Node->Left_child != NULL)//Tree_minimum
            {
                Node = Node->Left_child;
            }
            return Node;
        }
        else
        {
            while (Node->Parent != NULL)
            {

                if (Node = Node->Parent->Left_child) break;
                Node = Node->Parent;
            }
        }
        return Node->Parent;

    }




    // Удаление узла
    struct node* deleteNode(struct node* root, int key)
    {
        //  если дерево пустое
        if (root == NULL) return root;

        // что хотим удалить
        if (key < root->key)
            root->Left_child = deleteNode(root->Left_child, key);
        else if (key > root->key)
            root->Right_child = deleteNode(root->Right_child, key);
        else {
            // Если у узла один дочерний элемент или их нет
            if (root->Left_child == NULL)
            {
                struct node* temp = root->Right_child;
                free(root);//
                return temp;
            }
            else if (root->Right_child == NULL)
            {
                struct node* temp = root->Left_child;
                free(root);
                return temp;
            }

            // Если у узла два дочерних элемента
            struct node* temp = Tree_minimum(root->Right_child);

            // Помещаем inorder-преемника на место узла, который хотим удалить
            root->key = temp->key;

            // Удаляем inorder-преемника
            root->Right_child = deleteNode(root->Right_child, temp->key);
        }
        return root;
    }

    void Insert(node* n, int key) { //вставка по ключу
        bool inserted = false;	//проверка вставки
        if (root == nullptr) {		//если нет дерева, то создаем
            root = new node(key);
            return;
        }
        while (!inserted) {	//пока не произошла вставка
            if (key < n->key) {	//если ключ слева
                if (n->Left_child != nullptr) //если можно пойти дальше, идем
                    n = n->Left_child;
                else {
                    n->Left_child = new node(key);	//если нельзя, вставляем
                    inserted = true;	//вставка произошла 
                }
            }
            if (key > n->key) {		//если ключ справа
                if (n->Right_child != nullptr)
                    n = n->Right_child;
                else {
                    n->Right_child = new node(key);
                    inserted = true;
                }
            }
        }

    }

    void inorder(struct node* root) {
        if (root == NULL) return;
        inorder(root->Left_child);
        std::cout << root->key << " ";
        inorder(root->Right_child);
    }

    void preorder(struct node* root) {
        if (root == NULL) return;
        std::cout << root->key << " ";// сначала выводим ключ
        preorder(root->Left_child);//в левое поддерево все выводит
        preorder(root->Right_child);// после в правое 
    }

    void postorder(struct node* root) {
        if (root == NULL) return;
        postorder(root->Left_child);
        postorder(root->Right_child);
        std::cout << root->key << " ";
    }

    void InWidth(node* root)
    {
        if (root == NULL)
        {
            return;
        }

        queue<node*> q;
        q.push(root);

        while (!q.empty())
        {
            node* temp = q.front();

            std::cout << (temp->key) << ' ';

            if (temp->Left_child != nullptr)
            {
                q.push(temp->Left_child);
            }
            if (temp->Right_child != nullptr)
            {
                q.push(temp->Right_child);
            }
            q.pop();
        }
    }

    int hight(node* Node) {
        vector<node*> top;		//вектор вершин (ссылки)
        vector<node*> tmp;	//промежуточный вектор
        if (!Node) {
            return 0;
        }
        int h = 0;//счетчик высоты 
        top.push_back(Node);	//присваиваем первую вершину
        while (!top.empty()) {	//пока есть вершины
            for (int i = 0; i < top.size(); i++) {	//проходим по всем вершинам уровня
                if (top[i]->Left_child)				//формируем веришны след уровня
                    tmp.push_back(top[i]->Left_child);
                if (top[i]->Right_child)
                    tmp.push_back(top[i]->Right_child);
            }
            h++;
            top.clear();
            top = tmp;	//вектор вершин переходит на след уровень
            tmp.clear();
        }
        return h;
    }


public:

    void Insert(int key) {
        Insert(root, key);
    }

    void inorder() {
        inorder(root);
    }
    void preorder()
    {
        preorder(root);
    }
    void postorder() {
        postorder(root);

    }
    void deleteNode(int key) {
        deleteNode(root, key);
    }
    bool find(int key) {
        if (find(key, root)) return 1;
        else return 0;
    }
    void bft() {
        InWidth(root);
        ///bft(root);
    }
    void hight() {
        std::cout << hight(root);
    }
};

class RBT
{

    struct Node
    {
        int key;
        bool color;             //
        Node* Left_child, * Right_child, * Parent; //      
        Node(const int& v, const bool& c = RED, Node* l = nullptr, Node* r = nullptr, Node* p = nullptr) :key(v), color(c), Left_child(l), Right_child(r), Parent(p) {}
    };
    typedef Node* Node_rbt;

    Node_rbt root;
    Node_rbt nil;

    ///////////////////////////////////////////////// Повороты
    void left_rotate(Node* x)   //левый поворто
    {
        Node* y = x->Right_child;//указатель на правый потомок
        x->Right_child = y->Left_child;// замена правого потомка на левый правого потомка
        if (y != nil and y->Left_child != nil)
        {
            y->Left_child->Parent = x;  //меняем местами                                                  
        }
        y->Parent = x->Parent; //узел y стал новым корневым узлом, если его родительский узел был корневым
        if (x->Parent == nil)
            root = y;
        else if (x->Parent->Left_child == x)//если левый дочерний элемент родительского узла текущего узла равен текущему узлу
            x->Parent->Left_child = y;
        else
            x->Parent->Right_child = y;
        x->Parent = y;
        y->Left_child = x;
    }
    void right_rotate(Node* x)  //правый поворот
    {
        Node* y = x->Left_child;//указатель на левый потомок
        x->Left_child = y->Right_child;
        if (y->Right_child != nil)
            y->Right_child->Parent = x;
        y->Parent = x->Parent;
        if (x->Parent == nil)
            root = y;
        else if (x->Parent->Left_child == x)
            x->Parent->Left_child = y;
        else
            x->Parent->Right_child = y;
        x->Parent = y;
        y->Right_child = x;
    }



    ///////////////////////////////////////////////////////  Добавление элемента
    Node* insert_bst(Node*& p, Node*& r, const int& v)// обычное добавление кка в бинарном дереве поиска
    {
        Node* tmp = r;

        if (root == nil) {
            tmp = new Node(v, RED, nil, nil, p);
            if (p == nil)
                root = tmp;
            if (v > p->key)
                p->Right_child = tmp;
            else
                p->Left_child = tmp;
        }

        //если дерево пустое текущий элемент назначается корневым
        else                //в дереве есть элементы
        {
            while (true) {	//пока не произошла вставка
                if (v < tmp->key) {	//если ключ слева
                    if (tmp->Left_child != nil) //если можно пойти дальше, идем
                        tmp = tmp->Left_child;
                    else {
                        tmp->Left_child = new Node(v, RED, nil, nil, tmp);	//если нельзя, вставляем
                        //вставка произошла 
                        return tmp->Left_child;
                    }
                }
                if (v > tmp->key) {		//если ключ справа
                    if (tmp->Right_child != nil)
                        tmp = tmp->Right_child;
                    else {
                        tmp->Right_child = new Node(v, RED, nil, nil, tmp);
                        return tmp->Right_child;

                    }
                }
            }
        }
        return tmp;
    }


    //////////////////////////// вспомогательные функции
    Node* minimum(Node* r)
    {
        Node* p = r;
        while (r != nil)
        {
            p = r;
            r = r->Left_child;
        }
        return p;
    }
    Node* getNode(Node* r, const int& v)
    {
        if (r == nil)
            return nil;
        if (r->key == v)
            return r;
        else if (v < r->key)
            return getNode(r->Left_child, v);
        else
            return getNode(r->Right_child, v);
    }
    Node* getNode(const int& v)
    {
        return getNode(root, v);
    }

    //////////// удаление элемента 
    void rb_delete_fixup(Node* x)
    {
        while (x != root && x->color == BLACK)
        {
            if (x == x->Parent->Left_child)//если левый дочерний
            {
                Node* w = x->Parent->Right_child;//указатель на второй потомок родителя х "брат"
                if (w->color == RED)   // является красным                                    // 1
                {
                    w->color = BLACK;//перекрашиваем брата и родителя
                    x->Parent->color = RED;
                    left_rotate(x->Parent);//девый поворот
                    w = x->Parent->Right_child;
                }
                if (w->Left_child->color == BLACK and w->Right_child->color == BLACK)    // 2
                {// если оба дочерних элемента брата являются черными
                    w->color = RED;
                    x = x->Parent;
                }
                else
                {
                    if (w->Right_child->color == BLACK)                           // 3
                    {
                        w->Left_child->color = BLACK;
                        w->color = RED;
                        right_rotate(w);
                        w = x->Parent->Right_child;
                    }
                    w->color = x->Parent->color;                                 // 4
                    x->Parent->color = BLACK;
                    w->Right_child->color = BLACK;
                    left_rotate(x->Parent);
                    x = root;
                }
            }
            else/// тогда если правый дочерний
            {
                Node* w = x->Parent->Left_child;
                if (w->color == RED)                                         // 1
                {
                    w->color = BLACK;
                    x->Parent->color = RED;
                    right_rotate(x->Parent);
                    w = x->Parent->Left_child;
                }
                if (w->Right_child->color == BLACK && w->Left_child->color == RED)           // 2
                {
                    w->color = RED;
                    x = x->Parent;
                }
                else
                {
                    if (w->Left_child->color == BLACK)                             //3
                    {
                        w->Right_child->color = BLACK;
                        w->color = RED;
                        left_rotate(w);
                        w = x->Parent->Left_child;
                    }
                    w->color = x->Parent->color;                                 //  4
                    x->Parent->color = BLACK;
                    w->Left_child->color = BLACK;
                    right_rotate(x->Parent);
                    x = root;
                }
            }
        }
        x->color = BLACK;
    }
    void rb_transplant(Node*& u, Node*& v)//перемещение поддеревьев
    {
        if (u->Parent == nil)// если элемент является корнем
            root = v;
        else if (u == u->Parent->Left_child)// если левый потомок
            u->Parent->Left_child = v;
        else
            u->Parent->Right_child = v;//если правый потомок
        v->Parent = u->Parent;
    }
    void rb_delete(Node* z)
    {
        Node* y = z;
        bool delcol = y->color;
        Node* x = z;
        if (z->Left_child == nil)//нет левого потомка
        {
            x = z->Right_child;
            rb_transplant(z, z->Right_child);
        }
        else if (z->Right_child == nil)//нет правого потомка
        {
            x = z->Left_child;
            rb_transplant(z, z->Left_child);
        }
        else
        {// есть два дочерних узла
            y = minimum(z->Right_child);
            delcol = y->color;
            x = y->Right_child;
            if (y->Parent == z) x->Parent = y;
            else
            {
                rb_transplant(y, y->Right_child);
                y->Right_child = z->Right_child;
                y->Right_child->Parent = y;
            }
            rb_transplant(z, y);
            y->Left_child = z->Left_child;
            y->Left_child->Parent = y;
            y->color = z->color;
        }
        if (delcol == BLACK)
            rb_delete_fixup(x);
    }

    ////////////////////////////////////////////// Функции обходов
    void in_order(Node* r)
    {
        if (r == nil || r == nullptr)
            return;
        in_order(r->Left_child);
        std::cout << r->key << " " << r->color << endl;
        in_order(r->Right_child);
    }

    void pre_order(Node* r)
    {
        if (r == nil || r == nullptr)
            return;
        std::cout << r->key << " " << r->color << endl;
        pre_order(r->Left_child);
        pre_order(r->Right_child);
    }


    void post_order(Node* r)
    {
        if (r == nil || r == nullptr)
            return;

        post_order(r->Left_child);
        post_order(r->Right_child);
        std::cout << r->key << " " << r->color << endl;
    }



    void InWigh(Node* root)
    {
        if (root == NULL)
        {
            return;
        }

        queue<Node*> q;
        q.push(root);

        while (!q.empty())
        {
            Node* temp = q.front();

            std::cout << (temp->key) << " " << temp->color << endl;

            if (temp->Left_child != nil)
            {
                q.push(temp->Left_child);
            }
            if (temp->Right_child != nil)
            {
                q.push(temp->Right_child);
            }
            q.pop();
        }
    }

    int find_hight(Node* root) {
        vector<Node*> top;    //вектор вершин (ссылки)
        vector<Node*> tmp;  //промежуточный вектор
        if (!root) {
            return 0;
        }
        int h = 0;
        top.push_back(root);  //присваиваем первую вершину
        while (!top.empty()) {  //пока есть вершины
            for (int i = 0; i < top.size(); i++) {  //проходим по всем вершинам уровня

                if (top[i]->Left_child && top[i]->Left_child != nil)        //формируем веришны след уровня
                    tmp.push_back(top[i]->Left_child);
                if (top[i]->Right_child && top[i]->Right_child != nil)
                    tmp.push_back(top[i]->Right_child);
            }
            h++;
            top.clear();
            top = tmp;  //вектор вершин переходит на след уровень
            tmp.clear();
        }
        return h;
    }

    // функция для реализации поиска узла по ключу
    struct  Node* search(Node* node, int data) {
        if (node == nil || node->key == data) {
            return node;
        }
        if (data < node->key) {
            return search(node->Left_child, data);
        }
        return search(node->Right_child, data);
    }



public:
    RBT()
    {
        nil = new Node(-1, BLACK, nil, nil, nil);
        root = nil;
    }
    bool search(int key) {
        if (search(root, key)) return 1;
        else return 0;

    }


    void InWigh()
    {

        InWigh(root);
    }
    void post_order()
    {
        std::cout << "postorder:" << endl;
        post_order(root);
    }
    void pre_order()
    {
        std::cout << "preorder:" << endl;
        pre_order(root);
    }
    void in_order()
    {
        std::cout << "inorder: " << endl;
        in_order(root);
    }
    int find_height()
    {
        int h = find_hight(root);
        return h;
    }
    void rb_delete(const int& v) ///доп функция для удаления -  параметр ключ
    {
        Node* z = getNode(root, v);
        if (z == nil)
            return;
        rb_delete(z);
    }
    void insert(const int& v)//
    {
        Node* tmp = insert_bst(nil, root, v);//вставка элемента по его ключу  
        while (tmp->Parent->color == RED) //устранение возможных проблем 2 красных подряд 
        {// если родитель вставленного элемента красный
            if (tmp->Parent->Parent->Left_child == tmp->Parent) // родитель нового элемента - левый потомок
            {
                if (tmp->Parent->Parent->Right_child->color == RED) //случай когда "дядя" узла является красным               // 1
                {
                    tmp->Parent->color = BLACK; // перекрашиваем родителя деда и дядю
                    tmp->Parent->Parent->color = RED;
                    tmp->Parent->Parent->Right_child->color = BLACK;
                    tmp = tmp->Parent->Parent;//возвращаем "деда"
                }
                else //
                {
                    if (tmp->Parent->Right_child == tmp)  //если добавленный - узел правый потомок                     // 2
                    {
                        tmp = tmp->Parent;
                        ///
                        left_rotate(tmp);
                    }                                           // 3
                    tmp->Parent->color = BLACK;//если не правый потомок, то родительский узел делаем черным
                    tmp->Parent->Parent->color = RED; //
                    right_rotate(tmp->Parent->Parent);//
                }
            }
            else// все то же самое зеркально если родитель нового элемента правый  потомок
            {
                if (tmp->Parent->Parent->Left_child->color == RED)                 // 1
                {
                    tmp->Parent->color = BLACK;
                    tmp->Parent->Parent->color = RED;
                    tmp->Parent->Parent->Left_child->color = BLACK;
                    tmp = tmp->Parent->Parent;
                }
                else
                {
                    if (tmp->Parent->Left_child == tmp)                         // 2
                    {
                        tmp = tmp->Parent;
                        right_rotate(tmp);
                    }
                    tmp->Parent->color = BLACK;                        // 3
                    tmp->Parent->Parent->color = RED;
                    left_rotate(tmp->Parent->Parent);

                }
            }
        }

        root->color = BLACK;//цвет корневого эл та
    }


};

class AVL
{
    struct Node {
        int key, hight;
        Node* left = nullptr;
        Node* right = nullptr;
        Node(int key) {
            this->key = key;
            this->hight = 1;
        }
    } *root = nullptr;

    void swap(Node* a, Node* b) {	//обмен ключами для поворота
        int temp = a->key;
        a->key = b->key;
        b->key = temp;
    }

    int height(Node* node) {
        if (node == nullptr)
            return 0;
        return node->hight;
    }

    void new_hight(Node* n) {	//обнововление высоты 
        n->hight = max(height(n->left), height(n->right)) + 1;
    }

    bool find(Node* node, int key) const {
        while ((node != nullptr) and (key != node->key)) {
            if (key > node->key)
                node = node->right;
            else if (key < node->key)
                node = node->left;
            if (node == nullptr)
                return false;
            if (key == node->key)
                return true;
        }
    }

    Node* rotate_right(Node* node) {
        swap(node, node->left);

        Node* tmp = node->right;

        node->right = node->left;
        node->left = node->right->left;
        node->right->left = node->right->right;

        node->right->right = tmp;


        new_hight(node->right);
        new_hight(node);

        return node;

    }
    Node* rotate_left(Node* node) {
        swap(node, node->right);

        Node* tmp = node->left;

        node->left = node->right;
        node->right = node->left->right;
        node->left->right = node->left->left;

        node->left->left = tmp;


        new_hight(node->left);
        new_hight(node);

        return node;
    }

    int getBalance(Node* node) { //разность высот 
        if (node == nullptr)
            return 0;
        return height(node->left) - height(node->right);
    }

    Node* Insert(Node* node, int key) {
        if (node == nullptr)
            return new Node(key);
        if (key < node->key)
            node->left = Insert(node->left, key);
        else if (key > node->key)
            node->right = Insert(node->right, key);
        else
            return node;

        node->hight = 1 + max(height(node->left), height(node->right));
        int balance = getBalance(node);

        if (balance > 1 && key < node->left->key) //
            return rotate_right(node);

        if (balance < -1 && key > node->right->key)
            return rotate_left(node);

        if (balance > 1 && key > node->left->key) {
            node->left = rotate_left(node->left);
            return rotate_right(node);
        }

        if (balance < -1 && key < node->right->key) {
            node->right = rotate_right(node->right);
            return rotate_left(node);
        }

        return node;
    }

    Node* minValueNode(Node* node) {
        Node* current = node;
        while (current->left != NULL)
            current = current->left;
        return current;
    }

    Node* Delete(Node* node, int key) {
        if (node == nullptr)
            return node;
        if (key < node->key)
            node->left = Delete(node->left, key);
        else if (key > node->key)
            node->right = Delete(node->right, key);
        else {
            if ((node->left == nullptr) || (node->right == nullptr)) {
                Node* temp = node->left ? node->left : node->right;
                if (temp == nullptr) {
                    temp = node;
                    node = nullptr;
                }
                else
                    *node = *temp;
                free(temp);
            }
            else {
                Node* temp = minValueNode(node->right);
                node->key = temp->key;
                node->right = Delete(node->right, temp->key);
            }
        }

        if (node == nullptr)
            return node;

        node->hight = 1 + max(height(node->left), height(node->right));
        int balance = getBalance(node);

        if (balance > 1 && getBalance(node->left) >= 0)
            return rotate_right(node);

        if (balance > 1 && getBalance(node->left) < 0) {
            node->left = rotate_left(node->left);
            return rotate_right(node);
        }

        if (balance < -1 && getBalance(node->right) <= 0)
            return rotate_left(node);

        if (balance < -1 && getBalance(node->right) > 0) {
            node->right = rotate_right(node->right);
            return rotate_left(node);
        }

        return node;
    }



    void preorder(Node* node) const {/// сначала корень перходим к левому узлу  записываем снова корень и тд....дощли до минимального собираем оставшиеся правые по тому же принципу
        if (node != nullptr) {
            cout << node->key << " "; ///
            preorder(node->left);
            preorder(node->right);
        }
    }

    void postorder(Node* node) const {/// сначала самый минимальный  потом минимальный у его "брата" пока не закончатся потом правые по остаточному принципу в концу корень
        if (node == nullptr)
            return;

        postorder(node->left);
        postorder(node->right);
        cout << node->key << " ";
    }

    void inorder(Node* node) const { //по возрастанию
        if (node == nullptr)
            return;
        inorder(node->left);
        cout << node->key << " ";
        inorder(node->right);
    }

    void InWidht(Node* root) {
        if (root == nullptr) return;

        queue<Node*> q;
        q.push(root);

        while (!q.empty()) {
            Node* node = q.front();

            cout << node->key << " ";
            q.pop();

            if (node->left != nullptr)
            {
                q.push(node->left);
            }

            if (node->right != nullptr)
            {
                q.push(node->right);
            }
        }
    }

    int hight(Node* node) {
        vector<Node*> top;		//вектор вершин (ссылки)
        vector<Node*> tmp;	//промежуточный вектор
        if (!node) {
            return 0;
        }
        int h = 0;
        top.push_back(node);	//присваиваем первую вершину
        while (!top.empty()) {	//пока есть вершины
            for (int i = 0; i < top.size(); i++) {	//проходим по всем вершинам уровня
                if (top[i]->left)				//формируем веришны след уровня
                    tmp.push_back(top[i]->left);
                if (top[i]->right)
                    tmp.push_back(top[i]->right);
            }
            h++;
            top.clear();
            top = tmp;	//вектор вершин переходит на след уровень
            tmp.clear();
        }
        return h;
    }

public:
    bool find(int key) const {
        return(root, key);
    }
    void Insert(int key) {
        root = Insert(root, key);
    }
    void preorder() {
        preorder(root);
    }
    void postorder() {
        postorder(root);
    }
    void inorder() {
        inorder(root);
    }
    void InWidht() {
        InWidht(root);
    }
    void Delete(int key) {
        root = Delete(root, key);
    }

    void hight() {
        cout << hight(root);
    }


};

void MenuAVL()
{


    AVL avl;
    int key, choice;
    do {
        std::cout << endl << "---------------------------------------------------------------------" << endl;
        std::cout << "1. Добавить элемент" << endl;
        std::cout << "2. Есть ли элемент в дереве" << endl;
        std::cout << "3. Обход по дереву (preorder)" << endl;
        std::cout << "4. Обход по дереву (postorder)" << endl;
        std::cout << "5. Обход по дереву (inorder)" << endl;
        std::cout << "6. Обход по дереву В ширину" << endl;
        std::cout << "7. Удалить элемент по ключу" << endl;
        std::cout << "8. Вывести высоту дерева" << endl;
        std::cout << "0. Вернуться в главное меню" << endl;
        std::cout << "------------------------------------------------------------------" << endl;
        std::cout << endl << "Выберите действие: ";
        cin >> choice;
        std::cout << endl << "------------------------------------------------------------------" << endl;

        switch (choice)
        {
        case 1:
            std::cout << endl << "Введите элемент, который хотите добавить: ";
            cin >> key;
            avl.Insert(key);
            break;
        case 2:
            std::cout << endl << "Введите элемент, который хотите найти: ";
            cin >> key;
            if (avl.find(key))
                std::cout << "Элемент присутствует в дереве." << endl;
            else
                std::cout << "Элемент отсутствует в дереве." << endl;
            break;
        case 3:
            std::cout << endl << "Список: " << endl;
            avl.preorder();
            break;
        case 4:
            std::cout << endl << "Список: " << endl;
            avl.postorder();
            break;
        case 5:
            std::cout << endl << "Список: " << endl;
            avl.inorder();
            break;
        case 6:
            std::cout << endl << "Список: " << endl;
            avl.InWidht();
            break;
        case 7:
            std::cout << endl << "Введите значение элемента, который хотите удалить: ";
            int deleteKey;
            cin >> deleteKey;
            avl.Delete(deleteKey);
            break;
        case 8:
            std::cout << endl << "Высота дерева: ";
            avl.hight();
            break;


        default:
            break;
        }
    } while (choice != 0);

}

void MenuBST()
{
    Binary_Tree bst;
    int key, choice;
    do {
        std::cout << endl << "--------------------------------------------------------------------" << endl;
        std::cout << "1. Добавить элемент" << endl;
        std::cout << "2. Есть ли элемент в дереве" << endl;
        std::cout << "3. Обход по дереву (preorder)" << endl;
        std::cout << "4. Обход по дереву (postorder)" << endl;
        std::cout << "5. Обход по дереву (inorder)" << endl;
        std::cout << "6. Обход по дереву В ширину" << endl;
        std::cout << "7. Удалить элемент по ключу" << endl;
        std::cout << "8. Вывести высоту дерева" << endl;
        std::cout << "0. Вернуться в главное меню" << endl;
        std::cout << "------------------------------------------------------------------" << endl;
        std::cout << endl << "Выберите действие: ";
        cin >> choice;
        std::cout << endl << "------------------------------------------------------------------" << endl;

        switch (choice)
        {
        case 1:
            std::cout << endl << "Введите элемент, который хотите добавить: ";
            cin >> key;
            bst.Insert(key);
            break;
        case 2:
            std::cout << endl << "Введите элемент, который хотите найти: ";
            cin >> key;
            if (bst.find(key))
                std::cout << "Элемент присутствует в дереве." << endl;
            else
                std::cout << "Элемент отсутствует в дереве." << endl;
            break;
        case 3:
            std::cout << endl << "Список: " << endl;
            bst.preorder();
            break;
        case 4:
            std::cout << endl << "Список: " << endl;
            bst.postorder();
            break;
        case 5:
            std::cout << endl << "Список: " << endl;
            bst.inorder();
            break;
        case 6:
            std::cout << endl << "Список: " << endl;
            bst.bft();
            break;
        case 7:
            std::cout << endl << "Введите значение элемента, который хотите удалить: ";
            int deleteKey;
            cin >> deleteKey;
            bst.deleteNode(deleteKey);
            break;
        case 8:
            std::cout << endl << "Высота дерева: ";
            bst.hight();
            break;
        case 9:
            int k;
            k = 10;
            bst.Insert(k);
            k = 19;
            bst.Insert(k);
            k = 4;
            bst.Insert(k);
            k = 6;
            bst.Insert(k);
            k = 2;
            bst.Insert(k);
            k = 26;
            bst.Insert(k);
            k = 13;
            bst.Insert(k);

            break;


        default:
            break;
        }
    } while (choice != 0);
}

void MenuRBT()
{
    RBT rbt;

    int choice, key, h;
    bool founded;


    do {
        std::cout << endl << "---------------------------------------------------------------------" << endl;
        std::cout << "1. Добавить элемент" << endl;
        std::cout << "2. Найти высоту дерева" << endl;
        std::cout << "3. Вывести список на экран preorder" << endl;
        std::cout << "4. Вывести список на экран  postorder" << endl;
        std::cout << "5. Вывести список на экран  inorder" << endl;
        std::cout << "6. Вывести список на экран (по ширине)" << endl;
        std::cout << "7. Удалить элемент по ключу" << endl;
        std::cout << "8. Поиск элемента по ключу" << endl;
        std::cout << "0. Завершить программу" << endl;
        std::cout << "---------------------------------------------------------------------" << endl;
        std::cout << endl << "Выберите действие: ";
        cin >> choice;
        std::cout << "---------------------------------------------------------------------" << endl;

        switch (choice)
        {
        case 1:
            std::cout << endl << "Введите ключ для добавления: ";
            cin >> key;
            rbt.insert(key);
            break;

        case 2:
            h = rbt.find_height();
            std::cout << endl << h;
            break;

        case 3:
            std::cout << endl << " preorder Список: " << endl;
            rbt.pre_order();
            break;

        case 4:
            std::cout << endl << " postorder Список: " << endl;
            rbt.post_order();
            break;

        case 5:
            std::cout << endl << " inorder Список: " << endl;
            rbt.in_order();
            break;

        case 6:
            std::cout << endl << "Список: " << endl;
            rbt.InWigh();
            break;

        case 7:
            std::cout << endl << "Введите значение ключа для удаления: ";
            int delete_Key;
            cin >> delete_Key;
            rbt.rb_delete(delete_Key);
            break;
        case 8:
            std::cout << endl << "Введите ключ для поиска: ";
            cin >> key;
            if (rbt.search(key))
                std::cout << "Элемент присутствует в дереве." << endl;
            else
                std::cout << "Элемент отсутствует в дереве." << endl;


        default:
            break;
        }

    } while (choice != 0);

}

void time_insert()
{
    Binary_Tree bst_tree;
    AVL avl_tree;
    RBT rb_tree;
    int final_size = 100000;
    int step = 10000;
    srand(time(0));
    int* A = new int[final_size];
    random_device rd;
    // non-deterministic generator
    mt19937 gen(rd());  // to seed mersenne twister.
    uniform_int_distribution<> dist(1, 1000000);
    ///////// сделать проверку нормальную на повоторяющиеся элементы массива, на маленьких числах работает +-
    for (int i = 0; i < final_size; i++) {

        //int k = rand()%(500  * final_size);
        int k = dist(gen);

        int j;
        bool flag = true;

        for (j = 0; j < i; j++) {
            if (A[j] == k) {
                flag = false; break;
            }
        }
        if (flag)
        {
            A[i] = k;

        }
        else { i--; }


        // cout << i << endl;
    }
    auto begin = steady_clock::now();
    auto end = steady_clock::now();
    std::cout << endl << "Bремя добавления случайных элементов" << endl;

    long all_time = 0;//время
    std::cout << "RBTrandomInsert=["; //вывод времени вставки рандомного порядка 

    for (int j = 0; j < final_size - 1; j += step) {
        for (int i = 0; i < step; i++) {
            //std::cout << i + j << " ";
            if (i == 9000) {
                all_time = 0;//время

                begin = steady_clock::now();//начало таймера
                for (int k = 0; k < 1000; k++) {


                    rb_tree.insert(A[i + j + k]);

                }   end = steady_clock::now();
                all_time = duration_cast<nanoseconds>(end - begin).count();
                all_time /= 1000;
                std::cout << all_time << ", ";
                i += 1000;

            }
            else {
                rb_tree.insert(A[i + j]);
            }

        }
    }
    std::cout << "];" << endl;






    std::cout << "BSTrandomInsert=["; //вывод времени вставки рандомного порядка 

    all_time = 0;//время

    for (int j = 0; j < final_size - 1; j += step) {
        for (int i = 0; i < step; i++) {
            //  std::cout << i + j<<" ";
            if (i == 9000) {
                all_time = 0;//время

                begin = steady_clock::now();//начало таймера
                for (int k = 0; k < 1000; k++) {


                    bst_tree.Insert(A[i + j + k]);

                }   end = steady_clock::now();
                all_time = duration_cast<nanoseconds>(end - begin).count();
                all_time /= 1000;
                std::cout << all_time << ", ";
                i += 1000;

            }
            else {
                bst_tree.Insert(A[i + j]);
            }

        }
    }
    std::cout << "];" << endl;

    std::cout << "AVLrandomInsert=["; //вывод времени вставки рандомного порядка 


    for (int j = 0; j < final_size - 1; j += step) {
        for (int i = 0; i < step; i++) {
            // std::cout << i + j<<" ";
            if (i == 9000) {
                all_time = 0;//время


                for (int k = 0; k < 1000; k++) {
                    begin = steady_clock::now();//начало таймера

                    avl_tree.Insert(A[i + j + k]);
                    end = steady_clock::now();
                    all_time += duration_cast<nanoseconds>(end - begin).count();
                }

                all_time /= 1000;
                std::cout << all_time << ", ";
                i += 1000;

            }
            else {
                avl_tree.Insert(A[i + j]);
            }

        }
    }
    std::cout << "];" << endl;
}
void time_delete() {
    Binary_Tree bst_tree_d;
    AVL avl_tree_d;
    RBT rb_tree_d;
    int final_size = 100000;
    int step = 10000;
    srand(time(0));
    int* A = new int[final_size];
    random_device rd;
    // non-deterministic generator
    mt19937 gen(rd());  // to seed mersenne twister.
    uniform_int_distribution<> dist(1, 1000000);
    ///////// сделать проверку нормальную на повоторяющиеся элементы массива, на маленьких числах работает +-
    for (int i = 0; i < final_size; i++) {

        //int k = rand()%(500  * final_size);
        int k = dist(gen);

        int j;
        bool flag = true;

        for (j = 0; j < i; j++) {
            if (A[j] == k) {
                flag = false; break;
            }
        }
        if (flag)
        {
            A[i] = k;

        }
        else { i--; }


        // cout << i << endl;
    }
    auto begin = steady_clock::now();
    auto end = steady_clock::now();
    std::cout << endl << "Bремя удаления случайных элементов" << endl;

    long all_time = 0;//время
    std::cout << "RBTrandomInsert=["; //вывод времени вставки рандомного порядка 
    for (int j = 0; j < final_size - 1; j += step) {
        for (int i = 0; i < step; i++) {
            if (i == 9999) {

                for (int k = 0; k < 1000; k++) {

                    begin = steady_clock::now();//начало таймера
                    rb_tree_d.rb_delete(A[i + j]);
                    end = steady_clock::now();
                    all_time += duration_cast<nanoseconds>(end - begin).count();
                    rb_tree_d.insert(A[i + j]);
                }
                all_time /= 1000;
                std::cout << all_time << ", ";
            }
            else {
                rb_tree_d.insert(A[i + j]);
            }
        }
    }
    std::cout << "];" << endl;


    all_time = 0;//время
    std::cout << "BSTrandomInsert=["; //вывод времени вставки рандомного порядка 
    for (int j = 0; j < final_size - 1; j += step) {
        for (int i = 0; i < step; i++) {
            if (i == 9999) {

                for (int k = 0; k < 1000; k++) {

                    begin = steady_clock::now();//начало таймера
                    bst_tree_d.deleteNode(A[i + j]);
                    end = steady_clock::now();
                    all_time += duration_cast<nanoseconds>(end - begin).count();
                    bst_tree_d.Insert(A[i + j]);
                }
                all_time /= 1000;
                std::cout << all_time << ", ";
            }
            else {
                bst_tree_d.Insert(A[i + j]);
            }
        }
    }
    std::cout << "];" << endl;

    all_time = 0;//время
    std::cout << "AVLrandomInsert=["; //вывод времени вставки рандомного порядка 
    for (int j = 0; j < final_size - 1; j += step) {
        for (int i = 0; i < step; i++) {
            if (i == 9999) {

                for (int k = 0; k < 1000; k++) {

                    begin = steady_clock::now();//начало таймера
                    avl_tree_d.Delete(A[i + j]);
                    end = steady_clock::now();
                    all_time += duration_cast<nanoseconds>(end - begin).count();
                    avl_tree_d.Insert(A[i + j]);
                }
                all_time /= 1000;
                std::cout << all_time << ", ";
            }
            else {
                avl_tree_d.Insert(A[i + j]);
            }
        }
    }
    std::cout << "];" << endl;


}
void Hight_of_trees() {
    Binary_Tree H_BST;
    RBT H_RBT;
    AVL H_AVL;
    int tree_max = 100000;
    int tree_step = 10000;
    srand(time(0));
    int* A = new int[tree_max];
    random_device rd;
    // non-deterministic generator
    mt19937 gen(rd());  // to seed mersenne twister.
    uniform_int_distribution<> dist(1, 1000000);
    for (int i = 0; i < tree_max; i++) {

        //int k = rand()%(500  * final_size);
        int k = dist(gen);

        int j;
        bool flag = true;

        for (j = 0; j < i; j++) {
            if (A[j] == k) {
                flag = false; break;
            }
        }
        if (flag)
        {
            A[i] = k;

        }
        else { i--; }


        // cout << i << endl;
    }
    std::cout << endl << "%Высоты случайного дерева" << endl;
    std::cout << "RBTrandomHeight=[";//вывод времени вставки возрастающего порядка
    int k = 0; //счетчик запятых в выводе
    for (int j = 0; j < tree_max - 1; j += tree_step) {
        for (int i = 0; i < tree_step; i++) {
            if (i == tree_step - 1) {
                int h = H_RBT.find_height();
                std::cout << h << " ";
                H_RBT.insert(A[i + j]);

                if (k < 9) {
                    std::cout << ",";
                    k++;
                }
            }
            else {
                H_RBT.insert(A[i + j]);
            }
        }
    }
    std::cout << "];" << endl;

    std::cout << "BSTrandomHeight=[";//вывод времени вставки возрастающего порядка
    k = 0; //счетчик запятых в выводе
    for (int j = 0; j < tree_max - 1; j += tree_step) {
        for (int i = 0; i < tree_step; i++) {
            if (i == tree_step - 1) {
                H_BST.hight();

                H_BST.Insert(A[i + j]);

                if (k < 9) {
                    std::cout << ",";
                    k++;
                }
            }
            else {
                H_BST.Insert(A[i + j]);
            }
        }
    }
    std::cout << "];" << endl;

    std::cout << "AVLrandomHeight=[";//вывод времени вставки возрастающего порядка
    k = 0; //счетчик запятых в выводе
    for (int j = 0; j < tree_max - 1; j += tree_step) {
        for (int i = 0; i < tree_step; i++) {
            if (i == tree_step - 1) {
                H_AVL.hight();

                H_AVL.Insert(A[i + j]);

                if (k < 9) {
                    std::cout << ",";
                    k++;
                }
            }
            else {
                H_AVL.Insert(A[i + j]);
            }
        }
    }
    std::cout << "];" << endl;
}
void time_insert_S()
{
    Binary_Tree bst_tree;
    AVL avl_tree;
    RBT rb_tree;
    int final_size = 100000;
    int step = 10000;
    srand(time(0));
    int* A = new int[final_size];
    random_device rd;
    // non-deterministic generator
    mt19937 gen(rd());  // to seed mersenne twister.
    uniform_int_distribution<> dist(100000, 1000000);

    for (int i = 0; i < final_size; i++) {

        A[i] = i;
    }
    auto begin = steady_clock::now();
    auto end = steady_clock::now();
    std::cout << endl << "Bремя добавления случайных элементов" << endl;

    long all_time = 0;//время
    std::cout << "RBTrandomInsert=["; //вывод времени вставки рандомного порядка 

    for (int j = 0; j < final_size - 1; j += step) {
        for (int i = 0; i < step; i++) {
            //std::cout << i + j << " ";
            if (i == step - 1) {
                all_time = 0;//время
                int rand_element = dist(gen);

                begin = steady_clock::now();//начало таймера
                rb_tree.insert(rand_element);
                end = steady_clock::now();
                all_time = duration_cast<nanoseconds>(end - begin).count();
                std::cout << all_time << ", ";
                i++;

            }
            else {
                rb_tree.insert(A[i + j]);
            }

        }
    }
    std::cout << "];" << endl;


    std::cout << "BSTrandomInsert=["; //вывод времени вставки рандомного порядка 

    all_time = 0;//время

    for (int j = 0; j < final_size - 1; j += step) {
        for (int i = 0; i < step; i++) {
            //  std::cout << i + j<<" ";
            if (i == step - 1) {

                all_time = 0;//время
                int rand_element = dist(gen);

                begin = steady_clock::now();//начало таймера
                bst_tree.Insert(rand_element);
                end = steady_clock::now();
                all_time = duration_cast<nanoseconds>(end - begin).count();
                std::cout << all_time << ", ";
                i++;
            }
            else {
                bst_tree.Insert(A[i + j]);
            }

        }
    }
    std::cout << "];" << endl;

    std::cout << "AVLrandomInsert=["; //вывод времени вставки рандомного порядка 


    for (int j = 0; j < final_size - 1; j += step) {
        for (int i = 0; i < step; i++) {
            // std::cout << i + j<<" ";
            if (i == step - 1) {


                all_time = 0;//время
                int rand_element = dist(gen);

                begin = steady_clock::now();//начало таймера
                avl_tree.Insert(rand_element);
                end = steady_clock::now();
                all_time = duration_cast<nanoseconds>(end - begin).count();
                std::cout << all_time << ", ";
                i++;

            }
            else {
                avl_tree.Insert(A[i + j]);
            }

        }
    }
    std::cout << "];" << endl;
}
void time_delete_S() {
    Binary_Tree bst_tree_d;
    AVL avl_tree_d;
    RBT rb_tree_d;
    int final_size = 100000;
    int step = 10000;
    srand(time(0));
    int* A = new int[final_size];
    random_device rd;
    // non-deterministic generator

    ///////// сделать проверку нормальную на повоторяющиеся элементы массива, на маленьких числах работает +-
    for (int i = 0; i < final_size; i++) {

        A[i] = i;

        // cout << i << endl;
    }
    auto begin = steady_clock::now();
    auto end = steady_clock::now();
    std::cout << endl << "Bремя удаления случайных элементов" << endl;

    long all_time = 0;//время
    std::cout << "RBTrandomInsert=["; //вывод времени вставки рандомного порядка 
    for (int j = 0; j < final_size - 1; j += step) {
        for (int i = 0; i < step; i++) {
            if (i == 9999) {

                for (int k = 0; k < 1000; k++) {
                    mt19937 gen(rd());  // to seed mersenne twister.
                    uniform_int_distribution<> dist(1, i + j - 1);
                    int rand_element = dist(gen);
                    begin = steady_clock::now();//начало таймера
                    rb_tree_d.rb_delete(A[rand_element]);
                    end = steady_clock::now();
                    all_time += duration_cast<nanoseconds>(end - begin).count();
                    rb_tree_d.insert(A[rand_element]);
                }
                all_time /= 1000;
                std::cout << all_time << ", ";
            }
            else {
                rb_tree_d.insert(A[i + j]);
            }
        }
    }
    std::cout << "];" << endl;



    all_time = 0;//время
    std::cout << "AVLrandomInsert=[";
    for (int j = 0; j < final_size - 1; j += step) {
        for (int i = 0; i < step; i++) {
            if (i == 9999) {

                for (int k = 0; k < 1000; k++) {
                    mt19937 gen(rd());  // to seed mersenne twister.
                    uniform_int_distribution<> dist(1, i + j - 1);
                    int rand_element = dist(gen);
                    begin = steady_clock::now();//начало таймера
                    avl_tree_d.Delete(A[rand_element]);
                    end = steady_clock::now();
                    all_time += duration_cast<nanoseconds>(end - begin).count();
                    avl_tree_d.Insert(A[rand_element]);
                }
                all_time /= 1000;
                std::cout << all_time << ", ";
            }
            else {
                avl_tree_d.Insert(A[i + j]);
            }
        }
    }
    std::cout << "];" << endl;


}
void Hight_s() {
    Binary_Tree H_BST;
    RBT H_RBT;
    AVL H_AVL;
    int tree_max = 100000;
    int tree_step = 10000;
    srand(time(0));
    int* A = new int[tree_max];
    random_device rd;
    // non-deterministic generator
    mt19937 gen(rd());  // to seed mersenne twister.
    uniform_int_distribution<> dist(1, 1000000);
    for (int i = 0; i < tree_max; i++) {

        A[i] = i;



    }
    std::cout << endl << "%Высоты sorted дерева" << endl;
    std::cout << "RBTrandomHeight=[";//вывод времени вставки возрастающего порядка
    int k = 0; //счетчик запятых в выводе
    for (int j = 0; j < tree_max - 1; j += tree_step) {
        for (int i = 0; i < tree_step; i++) {
            if (i == tree_step - 1) {
                int h = H_RBT.find_height();
                std::cout << h << " ";
                H_RBT.insert(A[i + j]);

                if (k < 9) {
                    std::cout << ",";
                    k++;
                }
            }
            else {
                H_RBT.insert(A[i + j]);
            }
        }
    }
    std::cout << "];" << endl;

    std::cout << "BSTrandomHeight=[";//вывод времени вставки возрастающего порядка
    k = 0; //счетчик запятых в выводе
    for (int j = 0; j < tree_max - 1; j += tree_step) {
        for (int i = 0; i < tree_step; i++) {
            if (i == tree_step - 1) {
                H_BST.hight();

                H_BST.Insert(A[i + j]);

                if (k < 9) {
                    std::cout << ",";
                    k++;
                }
            }
            else {
                H_BST.Insert(A[i + j]);
            }
        }
    }
    std::cout << "];" << endl;

    std::cout << "AVLrandomHeight=[";//вывод времени вставки возрастающего порядка
    k = 0; //счетчик запятых в выводе
    for (int j = 0; j < tree_max - 1; j += tree_step) {
        for (int i = 0; i < tree_step; i++) {
            if (i == tree_step - 1) {
                H_AVL.hight();

                H_AVL.Insert(A[i + j]);

                if (k < 9) {
                    std::cout << ",";
                    k++;
                }
            }
            else {
                H_AVL.Insert(A[i + j]);
            }
        }
    }
    std::cout << "];" << endl;

}
int main()
{
    setlocale(LC_ALL, "Russian");
    int choiceTree;
    do {
        std::cout << "-------------------------------------------------------------------------";
        std::cout << endl << "Выберите дерево: " << endl;
        std::cout << "1. Binary Search Tree" << endl;
        std::cout << "2. AVL" << endl;
        std::cout << "3. Black-Red Tree" << endl;
        std::cout << "0. Выход";
        std::cout << endl << "------------------------------------------------------------------" << endl;
        cin >> choiceTree;
        switch (choiceTree)
        {
        case 1:
            MenuBST();
            break;

        case 2:
            MenuAVL();
            break;

        case 3:
            MenuRBT();
            break;

        case 4:
            time_insert();
            Hight_of_trees();
            time_delete();
            time_insert_S();
            Hight_s();
            time_delete_S();
            break;
        }

    } while (choiceTree != 0);
    return 0;

}



