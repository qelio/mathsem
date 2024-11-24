/**
 * @struct VUEPoint
 * @brief Структура, представляющая точку в системе координат VUE (Visual Understanding Environment).
 *
 * Эта структура содержит координаты x и y точки в 2D пространстве.
 */
struct VUEPoint
{
    double x; ///< Координата X точки.
    double y; ///< Координата Y точки.
};

/**
 * @class VUELink
 * @brief Класс, представляющий связь между двумя узлами VUE в окружении VUE.
 *
 * Этот класс используется для моделирования соединений между узлами, включая графические свойства, такие как положение, размер, стиль обводки и цвет.
 * Он предоставляет методы для установки и управления связями между различными типами сущностей, такими как узлы и формулы.
 */
class VUELink
{
    double x; ///< Координата X связи.
    double y; ///< Координата Y связи.
    double width; ///< Ширина связи.
    double height; ///< Высота связи.
    string strokeStyle; ///< Стиль обводки связи.
    string strokeColor; ///< Цвет обводки связи.
    string textColor; ///< Цвет текста связи.
    string strokeWidth; ///< Ширина обводки связи.
    string font; ///< Стиль шрифта связи.
    VUEPoint start; ///< Начальная точка связи.
    VUEPoint finish; ///< Конечная точка связи.
    VUENode * nodeStart; ///< Указатель на начальный узел связи.
    VUENode * nodeFinish; ///< Указатель на конечный узел связи.
    int numberInLayer; ///< Номер слоя связи.
    int childID; ///< Идентификатор дочерней сущности, связанной со связью.

public:
    /**
     * @brief Конструктор по умолчанию для класса VUELink.
     * Инициализирует VUELink значениями по умолчанию.
     */
    VUELink(void);

    /**
     * @brief Деструктор для класса VUELink.
     * Освобождает все ресурсы, связанные со связью.
     */
    ~VUELink(void);

    /**
     * @brief Параметризованный конструктор для создания VUELink с указанным идентификатором дочерней сущности и номером слоя.
     * @param childID_ Идентификатор дочерней сущности.
     * @param numberInLayer_ Номер слоя связи.
     */
    VUELink(int childID_, int numberInLayer_);

    /**
     * @brief Выводит детали VUELink в указанный поток вывода.
     * @param os Поток вывода, в который будут выведены детали связи.
     */
    void print(ostream& os);

    /**
     * @brief Вектор контрольных точек, определяющих форму связи.
     */
    vector <VUEPoint *> ctrlPoints;

    /**
     * @brief Устанавливает связь между двумя узлами VUE.
     * @param node1 Начальный узел связи.
     * @param node2 Конечный узел связи.
     */
    void setLink(VUENode * node1, VUENode * node2);

    /**
     * @brief Устанавливает связь между узлом формулы VUE и узлом множества VUE.
     * @param node1 Начальный узел связи (формула).
     * @param node2 Конечный узел связи (множество).
     */
    void setLink(VUEFormula * node1, VUESet * node2);

    /**
     * @brief Устанавливает связь между двумя узлами формулы VUE.
     * @param node1 Начальный узел связи (формула).
     * @param node2 Конечный узел связи (формула).
     */
    void setLink(VUEFormula * node1, VUEFormula * node2);

    /**
     * @brief Устанавливает идентификатор дочерней сущности и номер слоя для связи.
     * @param childID_ Идентификатор дочерней сущности.
     * @param numberInLayer_ Номер слоя связи.
     */
    void setIDs(int childID_, int numberInLayer_);

    /**
     * @brief Устанавливает тип связи.
     * @param ft Тип базовой сущности, определяющий тип связи.
     */
    void setLinkType(EntityBaseType ft);
};