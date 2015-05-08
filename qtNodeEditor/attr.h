#ifndef ATTR
#define ATTR


struct Attr
{
  enum attrType {BOOL, INT, FLOAT, COLOR, VEC3, MATRIX, STRING, CHOICE, GROUP, OTHER };

    Attr(const QString & sn, const QString &ln, attrType t, bool isO=0)
        : shortName(sn), longName(ln), isOutput(isO), type(t)
    {
    }

    QString shortName, longName;
    bool isOutput;
    attrType type;
};

class AttrList
{
public:

  void addAttr(Attr * a) {orderVector.push_back(a);}


  QVector<Attr *> orderVector;

};

#endif // ATTR

