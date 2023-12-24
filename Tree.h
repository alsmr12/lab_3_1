/**
@file
@brief файл с исходным кодом
 */


#include "Position.h"
#include "Container.h"
#include "Orientation.h"

#include <iostream>
#include <cstring>
#include <thread>
#include <vector>

/// @brief Шаблонное дерево
/** @details Шаблонное дерево
 @param root Указатель на узел дерева
 */
template <size_t N, typename ValueType>
class Tree {
public:
    /*
    struct Item {
        int key[N];      // массив ключей, определяющих элемент
        ValueType* info; // информация элемента

        Item(const int* k, ValueType* i) {
            std::memcpy(key, k, N * sizeof(int));
            info = i;
        }
    };
    */
    /// @brief Node - узел дерева
    /**
     * @param key массив ключей, определяющих элемент
     * @param info информация элемента
     * @param left указатель на левое поддерево
     * @param right указатель на правое поддерево
     */
    struct Node {
        //Item i;      // элемент
        int key[N];      // массив ключей, определяющих элемент
        ValueType* info; // информация элемента
        Node* left;  // левое  поддерево
        Node* right; // правое поддерево

        ///конструктор узла
        Node(const int* k, ValueType* i) : info(i), left(nullptr), right(nullptr) {
            std::memcpy(key, k, N * sizeof(int));
        }
    };

    Node* root; 

    Node* getRoot() const {
        return root;
    }
    /// Функция для добавления элемента в K-D дерево
    Node* insert(Node* tree, const int* keys, ValueType* info, int depth = 0) {
        if (tree == nullptr) {
            return new Node(keys, info);
        }

        int axis = depth % N;

        if (keys[axis] < tree->key[axis]) {
            tree->left = insert(tree->left, keys, info, depth + 1);
        } else {
            tree->right = insert(tree->right, keys, info, depth + 1);
        }

        return tree;
    }

    /// Функция для поиска элементов в заданном диапазоне
    void searchInRange(Node* tree, const int* minKeys, const int* maxKeys, int depth = 0) {
        if (tree == nullptr) {
            return;
        }

        int axis = depth % N;

        if (minKeys[axis] <= tree->key[axis]) {
            searchInRange(tree->left, minKeys, maxKeys, depth + 1);
        }

        if (maxKeys[axis] >= tree->key[axis]) {
            searchInRange(tree->right, minKeys, maxKeys, depth + 1);
        }

        /// @warning Если медиана узла полностью входит в заданный диапазон, вывести информацию
        bool isInRange = true;
        for (size_t i = 0; i < N; ++i) {
            if (tree->key[i] < minKeys[i] || tree->key[i] > maxKeys[i]) {
                isInRange = false;
                break;
            }
        }

        if (isInRange) {
            std::cout << "Keys: [";
            for (size_t i = 0; i < N; ++i) {
                std::cout << tree->key[i] << " ";
            }
            std::cout << "], Info: " << tree->info << std::endl;
        }
    }

    /// Функция для обхода дерева и вывода его элементов
    void traverse(Node* tree) const{
        if (tree == nullptr) {
            return;
        }

        traverse(tree->left);
        std::cout << "Keys: [";
        for (size_t i = 0; i < N; ++i) {
            std::cout << tree->key[i] << " ";
        }
        std::cout << "], Info: " << tree->info << std::endl;
        traverse(tree->right);
    }
    /*
    /// Функция для удаления элемента из K-D дерева
    Node* deleteNode(Node* tree, const int* keys, int depth = 0) {
        if (tree == nullptr) {
            return nullptr;
        }

        int axis = depth % N;

        if (keys[axis] < tree->key[axis]) {
            tree->left = deleteNode(tree->left, keys, depth + 1);
        } else if (keys[axis] > tree->key[axis]) {
            tree->right = deleteNode(tree->right, keys, depth + 1);
        } else {
            /// Найден элемент для удаления

            if (tree->right == nullptr) {
                /// Узел без правого поддерева
                Node* temp = tree->left;
                delete tree;
                return temp;
            } else {
                /// Узел с правым поддеревом
                Node* successor = tree->right;
                while (successor->left != nullptr) {
                    successor = successor->left;
                }

                /// Копируем ключи и информацию из преемника в текущий узел
                std::memcpy(tree->key, successor->key, N * sizeof(int));
                std::swap(tree->info, successor->info);

                /// Рекурсивно удаляем преемника из правого поддерева
                tree->right = deleteNode(tree->right, successor->key, depth + 1);
            }
        }

        return tree;
    }*/
    const int k = 3;

    Node *minNode(Node *x, Node *y, Node *z, int d)
    {
        Node *res = x;
        if (y != NULL && y->key[d] < res->key[d])
            res = y;
        if (z != NULL && z->key[d] < res->key[d])
            res = z;
        return res;
    }

    Node *findMinRec(Node* root, int d, unsigned depth)
    {
        // Base cases
        if (root == NULL)
            return NULL;

        // Current dimension is computed using current depth and total
        // dimensions (k)
        unsigned cd = depth % k;

        // Compare point with root with respect to cd (Current dimension)
        if (cd == d)
        {
            if (root->left == NULL)
                return root;
            return findMinRec(root->left, d, depth+1);
        }

        // If current dimension is different then minimum can be anywhere
        // in this subtree
        return minNode(root,
                       findMinRec(root->left, d, depth+1),
                       findMinRec(root->right, d, depth+1), d);
    }

// A wrapper over findMinRec(). Returns minimum of d'th dimension
    Node *findMin(Node* root, int d)
    {
        // Pass current level or depth as 0
        return findMinRec(root, d, 0);
    }

// A utility method to determine if two Points are same
// in K Dimensional space
    bool arePointsSame(const int* p1, const int*p2)
    {
        // Compare individual pointinate values
        for (int i = 0; i < k; ++i)
            if (p1[i] != p2[i])
                return false;

        return true;
    }

// Copies point p2 to p1
    void copyPoint(int* k1, int* k2)
    {
        for (int i=0; i<k; i++)
            k1[i] = k2[i];
    }

// Function to delete a given point 'point[]' from tree with root
// as 'root'.  depth is current depth and passed as 0 initially.
// Returns root of the modified tree.
    Node *deleteNode(Node *root, const int* keys, int depth = 0)
    {
        // Given point is not present
        if (root == NULL)
            return NULL;
        // Find dimension of current node
        int cd = depth % k;

        // If the point to be deleted is present at root
        if (arePointsSame(root->key, keys))
        {
            // 2.b If right child is not NULL
            if (root->right != NULL)
            {
                // Find minimum of root's dimension in right subtree
                Node *min = findMin(root->right, cd);

                // Copy the minimum to root
                copyPoint(root->key, min->key);

                // Recursively delete the minimum
                root->right = deleteNode(root->right, min->key, depth+1);
            }
            else if (root->left != NULL) // same as above
            {
                Node *min = findMin(root->left, cd);
                copyPoint(root->key, min->key);
                root->right = deleteNode(root->left, min->key, depth+1);
            }
            else // If node to be deleted is leaf node
            {
                delete root;
                return nullptr;
            }
            return root;
        }

        // 2) If current node doesn't contain point, search downward
        if (keys[cd] < root->key[cd])
            root->left = deleteNode(root->left, keys, depth+1);
        else
            root->right = deleteNode(root->right, keys, depth+1);
        return root;
    }
//////////////////////////////////

    Node* find(Node* tree, const int* searchKey, int depth = 0){
        if (tree == nullptr) {
            return nullptr;  /// Node not found
        }

        int axis = depth % N;

        if (std::memcmp(searchKey, tree->key, N * sizeof(int)) == 0) {
            /// Node with the given key found
            return tree;
        } else if (searchKey[axis] < tree->key[axis]) {
            /// Search in the left subtree
            return find(tree->left, searchKey, depth + 1);
        } else {
        /// Search in the right subtree
            return find(tree->right, searchKey, depth + 1);
        }
    }
    Node* findInsertionPlace(const int* keys, Node* tree = nullptr, int depth = 0) {
        if (tree == nullptr) {
            /// Если дерево пусто, вернуть nullptr, чтобы указать, что места для вставки не найдено
            return nullptr;
        }

        int axis = depth % N;

        if (keys[axis] < tree->key[axis]) {
            if (tree->left == nullptr) {
                /// Если левого поддерева нет, вернуть текущий узел
                return tree;
            } else {
                /// Рекурсивно искать место в левом поддереве
                return findInsertionPlace(keys, tree->left, depth + 1);
            }
        } else {
            if (tree->right == nullptr) {
                /// Если правого поддерева нет, вернуть текущий узел
                return tree;
            } else {
                /// Рекурсивно искать место в правом поддереве
                return findInsertionPlace(keys, tree->right, depth + 1);
            }
        }
    }
    void automatically_insert(const int* keys, ValueType *info, int depth = 0){
        Node *insertion_place = findInsertionPlace(keys, root, depth);
        if(insertion_place != nullptr){
            insertion_place->left = insert(insertion_place->left, keys, info, depth + 1);
        }
    }

    ValueType* search(Node* tree, const int* keys, int depth = 0) {
    if (tree == nullptr) {
        return nullptr;
    }

    int axis = depth % N;

    if (keys[axis] == tree->key[axis]) {
        /// Найден элемент
        return tree->info;
    }

    if (keys[axis] < tree->key[axis]) {
        return search(tree->left, keys, depth + 1);
    } else {
        return search(tree->right, keys, depth + 1);
    }
}

    Node* findInsertionPlaceThread(const int* keys, Node* tree, int startDepth, int depthIncrement) {
        if (tree == nullptr) {
            /// Если дерево пусто, вернуть nullptr, чтобы указать, что места для вставки не найдено
            return nullptr;
        }

        int axis = (startDepth % N);

        if (keys[axis] < tree->key[axis]) {
            if (tree->left == nullptr) {
                /// Если левого поддерева нет, вернуть текущий узел
                return tree;
            } else {
                /// Рекурсивно искать место в левом поддереве
                return findInsertionPlaceThread(keys, tree->left, startDepth + depthIncrement, depthIncrement);
            }
        } else {
            if (tree->right == nullptr) {
                /// Если правого поддерева нет, вернуть текущий узел
                return tree;
            } else {
                /// Рекурсивно искать место в правом поддереве
                return findInsertionPlaceThread(keys, tree->right, startDepth + depthIncrement, depthIncrement);
            }
        }
    }

// Метод для поиска места вставки в многопоточном режиме
/*
    Node* findInsertionPlaceMultiThread(const int* keys, int threadCount = 1) {
        std::vector<std::thread> threads;
        std::vector<Node*> results(threadCount, nullptr);

        for (int i = 0; i < threadCount; ++i) {
            threads.emplace_back([this, i, keys, &results]() {
                results[i] = findInsertionPlaceThread(keys, root, i, threadCount);
            });
        }

        for (auto& thread : threads) {
            thread.join();
        }

        // Выбираем первый найденный результат (не nullptr)
        for (auto& result : results) {
            if (result != nullptr) {
                return result;
            }
        }

        return nullptr;
    }

*/

/*
bool isKeyFree(const int* keys) const {
        return find(root, keys) == nullptr;
}

int* findFreeKeyInRange(Node* tree, const int* minKeys, const int* maxKeys, int depth = 0) {
    if (tree == nullptr) {
        // Если узел пуст, возвращаем nullptr
        return nullptr;
    }

    int axis = depth % N;

    if (minKeys[axis] <= tree->key[axis]) {
        return findFreeKeyInRange(tree->left, minKeys, maxKeys, depth + 1);
    }

    if (maxKeys[axis] >= tree->key[axis]) {
        return findFreeKeyInRange(tree->right, minKeys, maxKeys, depth + 1);
    }

    // Если медиана узла полностью входит в заданный диапазон, проверяем, свободен ли ключ
    bool isInRange = true;
    for (size_t i = 0; i < N; ++i) {
        if (tree->key[i] < minKeys[i] || tree->key[i] > maxKeys[i]) {
            isInRange = false;
            break;
        }
    }

    if (isInRange && isKeyFree(tree->key)) {
        // Если ключ свободен, возвращаем его
        return tree->key;
    }

    // Рекурсивный вызов для поиска в левом и правом поддеревьях
    int* leftResult = findFreeKeyInRange(tree->left, minKeys, maxKeys, depth + 1);
    int* rightResult = findFreeKeyInRange(tree->right, minKeys, maxKeys, depth + 1);

    // Если хотя бы один из ключей свободен, возвращаем его
    if (leftResult != nullptr) {
        return leftResult;
    } else {
        return rightResult;
    }
}
*/

/*
    // Метод для оформления поступления нового контейнера с автоматическим поиском подходящего места
    void insertContainer(Node*& tree, ValueType* info, int depth = 0) {
        if (tree == nullptr) {
            // Если дерево пусто, вставляем контейнер в это место
            tree = new Node(info->get_keys(), info);
            return;
        }

        int axis = depth % N;

        // Выбираем поддерево для поиска подходящего места
        Node*& subtree = (info->get_keys()[axis] < tree->key[axis]) ? tree->left : tree->right;

        // Рекурсивно ищем место для вставки
        insertContainer(subtree, info, depth + 1);
    }

    bool is_position_free(const int* keys, const Size& container_size, int container_weight) const {
        return is_position_free_recursive(root, keys, container_size, container_weight, 0);
    }

    // Рекурсивная функция для проверки, свободно ли место для контейнера
    bool is_position_free_recursive(Node* tree, const int* keys, const Size& container_size, int container_weight, int depth) const {
    if (tree == nullptr) {
        return true;  // Место свободно, если мы достигли конца дерева
    }

    int axis = depth % N;

    // Проверяем, перекрываются ли контейнеры
    if (keys[axis] < tree->key[axis] + container_size.get_length() &&
        keys[axis] + container_size.get_length() > tree->key[axis]) {

        // Контейнеры перекрываются в данном измерении, продолжаем проверку для других измерений
        for (size_t i = 0; i < N; ++i) {
            if (static_cast<size_t>(i) != static_cast<size_t>(axis) &&
    (keys[i] >= tree->key[i] + container_size.get_width() ||
     keys[i] + container_size.get_width() <= tree->key[i])) {
    // Контейнеры не перекрываются в других измерениях, продолжаем проверку
    continue;
}

            // Контейнеры перекрываются в других измерениях, это место занято
            return false;
        }

        // Дополнительно проверяем, что масса нового контейнера не превышает массу хрупкого контейнера
        if (tree->info->is_fragile() && container_weight > tree->info->get_weight()) {
            // Масса нового контейнера больше массы хрупкого контейнера, это место нельзя использовать
            return false;
        }

        // Место занято
        return false;
    }

    // Переходим к левому или правому поддереву в зависимости от текущего ключа
    if (keys[axis] < tree->key[axis]) {
        return is_position_free_recursive(tree->left, keys, container_size, container_weight, depth + 1);
    } else {
        return is_position_free_recursive(tree->right, keys, container_size, container_weight, depth + 1);
    }
}
*/



    /*
    std::list<ValueType> getContainersList() const {
        std::list<ValueType> result;
        traverse(root, result);
        return result;
    }

    // После объявления класса Tree добавьте следующую функцию traverse:
    void traverse(Node* tree, std::list<ValueType>& result) const {
        if (tree == nullptr) {
            return;
        }

        traverse(tree->left, result);
        result.push_back(*(tree->info));  // Разыменовываем указатель Container**
        traverse(tree->right, result);
    }
    
    
    void change_orintation(Node* tree, const int* searchKey, Orientation orientation){
        auto it = find(tree, searchKey);
        if(it != nullptr){
            it->info.set_orientation(orientation);
        }
    }
    

   // Рекурсивная функция для обхода k-d дерева
   
    void traverseKDTree(Node* tree, std::function<void(Node*)> visit, int depth = 0) {
        if (tree == nullptr) {
            return;
        }

        traverseKDTree(tree->left, visit, depth + 1);
        visit(tree);
        traverseKDTree(tree->right, visit, depth + 1);
    }
    
    int get_maximal_containers_size(const Size& size, bool allow_rotation) const {
    int max_count = 0;

    // Рекурсивная функция для обхода k-d дерева
    auto traverseKDTree = [&](const Tree<3, Container*>::Node* node) {
        if (node == nullptr) {
            return;
        }

        Size& container_size = node->info->get_dimensions();

        if ((container_size.equals(size)) || (allow_rotation && (container_size.transpose().equals(size)))) {
            max_count++;
        }

        // Рекурсивно обходим левое и правое поддерево
        traverseKDTree(node->left);
        traverseKDTree(node->right);
    };

    // Начинаем обход с корня k-d дерева
    traverseKDTree(containerTree.getRoot());

    return max_count;
}*/

};
