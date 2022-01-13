#include "Nodes.h"

#include <memory>

typedef struct {
    int x;
    int y;
} coordinates;

std::vector<FunctionUnit*> functions;
std::vector<std::exception> errors;

std::vector<std::vector<std::string>> labirint; //0-тупик, 1-текущее, 2-пустота, 3-выходы
coordinates cur_coordinates;
int radius;
auto side = new MemoryUnit(new Int(-1));

VarLeaf::VarLeaf(int line, const std::string &s) {
    line_number = line;
    name = s;
}

NodeType VarLeaf::get_type() {
    return type;
}

IntLeaf::IntLeaf(int line, std::int32_t value) {
    data = new MemoryUnit(new Int(value));
    line_number = line;
}

IntLeaf::IntLeaf(MemoryUnit m) {
    data = new MemoryUnit(m);
}

NodeType IntLeaf::get_type() {
    return type;
}

ShortLeaf::ShortLeaf(MemoryUnit m) {
    data = new MemoryUnit(m);
}

ShortLeaf::ShortLeaf(int line, std::int16_t value) {
    data = new MemoryUnit(new Short(value));
    line_number = line;
}

NodeType ShortLeaf::get_type() {
    return type;
}

BoolLeaf::BoolLeaf(MemoryUnit m) {
    data = new MemoryUnit(m);
}

BoolLeaf::BoolLeaf(int line, Logic value) {
    data = new MemoryUnit(new Bool(value));
    line_number = line;
}

NodeType BoolLeaf::get_type() {
    return type;
}

AddNode::AddNode(int line, Node* l, Node* r) {
    if (l && r) {
        line_number = line;
        left = l;
        right = r;
    }
    else {
        errors.push_back(SyntaxError("Add must have 2 parameters"));
    }
}

NodeType AddNode::get_type() {
    return type;
}

SubNode::SubNode(int line, Node* l, Node* r) {
    if (l && r) {
        line_number = line;
        left = l;
        right = r;
    }
    else {
        errors.push_back(SyntaxError("Sub must have 2 parameters"));
    }
}

NodeType SubNode::get_type() {
    return type;
}

AndNode::AndNode(int line, Node* l, Node* r) {
    if (l && r) {
        line_number = line;
        left = l;
        right = r;
    }
    else {
        errors.push_back(SyntaxError("And must have 2 parameters"));
    }
}

NodeType AndNode::get_type() {
    return type;
}

NandNode::NandNode(int line, Node* l, Node* r) {
    if (l && r) {
        line_number = line;
        left = l;
        right = r;
    }
    else {
        errors.push_back(SyntaxError("Nand must have 2 parameters"));
    }
}

NodeType NandNode::get_type() {
    return type;
}

OrNode::OrNode(int line, Node* l, Node* r) {
    if (l && r) {
        left = l;
        right = r;
    }
    else {
        errors.push_back(SyntaxError("Or must have 2 parameters"));
    }
}

NodeType OrNode::get_type() {
    return type;
}

NorNode::NorNode(int line, Node* l, Node* r) {
    if (l && r) {
        line_number = line;
        left = l;
        right = r;
    }
    else {
        errors.push_back(SyntaxError("Nor must have 2 parameters"));
    }
}

NodeType NorNode::get_type() {
    return type;
}

SmallerNode::SmallerNode(int line, Node* l, Node* r) {
    if (l && r) {
        line_number = line;
        left = l;
        right = r;
    }
    else {
        errors.push_back(SyntaxError("Smaller must have 2 parameters"));
    }
}

NodeType SmallerNode::get_type() {
    return type;
}

LargerNode::LargerNode(int line, Node* l, Node* r) {
    if (l && r) {
        line_number = line;
        left = l;
        right = r;
    }
    else {
        errors.push_back(SyntaxError("Larger must have 2 parameters"));
    }
}

NodeType LargerNode::get_type() {
    return type;
}

SetNode::SetNode(int line, Node* l, Node* r) {
    if (l && r) {
        line_number = line;
        left = l;
        right = r;
    }
    else {
        errors.push_back(SyntaxError("Set must have lvalue and rvalue"));
    }
}

NodeType SetNode::get_type() {
    return type;
}

LoopNode::LoopNode(int line, Node* cond, Node* c) {
    if (cond == nullptr) {
        errors.push_back(SyntaxError("Loop must have  a condition"));
    }
    else {
        line_number = line;
        condition = cond;
        code = c;
    }
}

NodeType LoopNode::get_type() {
    return type;
}

// FDeclNode::FDeclNode(int line, std::string n, std::shared_ptr<Node> c, std::vector<std::pair<Datatypes, std::string>> p,
//                      std::shared_ptr<Node> r) {
//     line_number = line;
//     name = n;
//     code = c;
//     params = p;
//     ret = r;
//     func = std::make_shared<FunctionUnit>(name, params);
//     func->set_link(std::shared_ptr<FDeclNode>(this));
// }

NodeType FDeclNode::get_type() {
    return type;
}

FcallNode::FcallNode(int line, std::string n, std::vector<Node*> p) : name(n), params(p) {
    line_number = line;
}

NodeType FcallNode::get_type() {
    return type;
}

SizeofNode::SizeofNode(int line, Datatypes t) {
    if ( t == Datatypes::INT) {
        line_number = line;
        next = new IntLeaf(MemoryUnit(new Int()));
    } else if (t == Datatypes::SHORT) {
        line_number = line;
        next = new IntLeaf(MemoryUnit(new Short()));
    } else if (t ==Datatypes::BOOL) {
        line_number = line;
        next = new IntLeaf(MemoryUnit(new Bool()));
    } else {
        errors.push_back(SyntaxError("Can't be computed for a vector"));
    }
}

SizeofNode::SizeofNode(int line, std::string n) {
    line_number = line;
    next = new VarLeaf(line, n);
}

NodeType SizeofNode::get_type() {
    return type;
}

IfNode::IfNode(int line, Node* c, Node* i, Node* e) {
    if (c) {
        line_number = line;
        condition = c;
        if_code = i;
        else_code = e;
    }
    else {
        errors.push_back(SyntaxError("If must have a condition"));
    }
}

NodeType IfNode::get_type() {
    return type;
}

VecDeclNode::VecDeclNode(int line, int v, std::string n, std::vector<Node*> e,
                         std::vector<Node*> d) :  vecof_count(v), name(n), elems(e), dims(d), main(true) {
    line_number = line;
}

VecDeclNode::VecDeclNode(int line, std::vector<Node*> e) : elems(e) {
    name = {}; dims = {}; vecof_count = {}; main = false;
    line_number = line;
}

void VecDeclNode::init(std::vector<Node*> v, Memory* m) {
    std::pair<int, Object*> p;
    auto k = false;
    auto s = 0;
    for (auto it = v.begin(); it != v.end(); it++) {
        if ((*it)->get_type() == NodeType::VECDECLNODE) {
            if (it == v.begin()) {
                s = dynamic_cast<VecDeclNode*>(*it)->elems.size();
            } else {
                if (s != dynamic_cast<VecDeclNode*>(*it)->elems.size()) {
                    errors.push_back(SyntaxError("Different sizes"));
                }
            }
            init(dynamic_cast<VecDeclNode*>(*it)->elems, m);
            k = true;
        } else if (k && (*it)->get_type() != NodeType::VECDECLNODE) {
            errors.push_back(SyntaxError("Vector error"));
        } else if (it != v.begin() && !k && (*it)->get_type() != NodeType::VECDECLNODE) {
            throw SyntaxError("Vector error");
        } else {
            auto n = exec(*it, m);
            if (!n) {
                errors.push_back(SyntaxError("Error in initialization"));
            }
            objects.push_back(n->data);
        }
    }
    if (k) {
        real_dims.push_back(s);
    }
}

NodeType VecDeclNode::get_type() {
    return type;
}

IndexNode::IndexNode(int line, Node* n, std::vector<Node*> e) : next(n), elems(e) {
    if (!next) {
        errors.push_back(SyntaxError("Vector missed"));
    }
    line_number = line;
}

NodeType IndexNode::get_type() {
    return type;
}

VarDeclNode::VarDeclNode(int line, std::string n, Datatypes t, Node* init_node) {
    line_number = line;
    Object* obj;
    if (t == Datatypes::INT) {
        obj = new Int();
    }
    else if (t == Datatypes::SHORT) {
        obj = new Short();
    }
    else {
        obj = new Bool();
    }
    var = new VariableUnit(n, obj);
    init = init_node;
}

VarDeclNode::VarDeclNode(std::string n, MemoryUnit* m) {
    name = n;
    var = new VariableUnit(n, m);
}

NodeType VarDeclNode::get_type() {
    return type;
}

VarListNode::VarListNode(int line, std::pair<Datatypes, std::vector<VarDeclaration>> p) {
    t = p.first;
    line_number = line;
    for (auto it : p.second) {
        auto e = new VarDeclNode(line, it.name, t, it.init);
        vec.push_back(e);
    }
}

StatementList::StatementList(Node* n) {
    if (n)
        vec.push_back(n);
}

void StatementList::add(Node* n) {
    if (n)
        vec.push_back(n);
}

NodeType RightNode::get_type() {
    return type;
}

NodeType LeftNode::get_type() {
    return type;
}

NodeType MoveNode::get_type() {
    return type;
}

NodeType LmsNode::get_type() {
    return type;
}

FDeclNode::FDeclNode(int line, std::string n, Node* c, std::vector<std::pair<Datatypes, std::string>> p, Node* r) {
    line_number = line;
    name = n;
    code = c;
    params = p;
    ret = r;
    func = new FunctionUnit(name, params);
    func->set_link(this);
    functions.push_back(func);
}

PrintNode::PrintNode(int line, Node* n) {
    line_number = line;
    if (!n) {
        errors.push_back(SyntaxError("Print must have one parameter"));
    } else {
        next = n;
    }
}

NodeType PrintNode::get_type() {
    return type;
}


// std::shared_ptr<Memory> init_global(std::shared_ptr<Node> root) {
//     auto m = std::make_shared<Memory>();
//     auto lst = std::dynamic_pointer_cast<StatementList>(root)->vec;
//     for (auto it : lst) {
//         if (it->get_type() == NodeType::FDECLNODE) {
//             continue;
//         } else if(it->get_type() == NodeType::VECDECLNODE || it->get_type() == NodeType::VARDECLNODE || it->get_type() == NodeType::VARLIST) {
//             exec(it, m);
//         } else {
//             errors.push_back(SyntaxError("There can only be definitions in the global scope"));
//         }
//     }
//     return m;
// }

void init(Memory* m, Node* root) {
    auto lst = dynamic_cast<StatementList*>(root)->vec;
    Node* work;
    int count = 0;
    for (auto it : lst) {
        if (it->get_type() == NodeType::FDECLNODE) {
            auto f = dynamic_cast<FDeclNode*>(it);
            if (f->name == "work") {
                work = it;
                count++;
                if (count > 1) {
                    errors.push_back(SyntaxError("There can be only 1 function named work"));
                }

            }
        } else if(it->get_type() == NodeType::VECDECLNODE || it->get_type() == NodeType::VARDECLNODE || it->get_type() == NodeType::VARLIST) {
            exec(it, m);
        } else {
            errors.push_back(SyntaxError("There can only be definitions in the global scope"));
        }
    }
    if (dynamic_cast<FDeclNode*>(work)->params.size() != 0) {
        errors.push_back(SyntaxError("The work function must have no parameters"));
    }
    auto t = dynamic_cast<FDeclNode*>(work)->code;
    exec(t, m);
}
//     std::shared_ptr<FunctionUnit> work;
//     int count = 0;
//     for (auto it : functions) {
//         if (it->name == "work") {
//             count++;
//             work = it;
//             if (count > 1) {
//                 errors.push_back(SyntaxError("There can be only 1 function named work"));
//             }
//         }
//     }
//     if (work->params.size() != 0) {
//                 errors.push_back(SyntaxError("The work function must have no parameters"));
//     exec(work->link, m);
//     }
//  }

void init_labirint(std::string filename) {
    std::ifstream file("lab");
    std::string s;
    std::string prob = " ";
    std::vector<std::vector<char>> vec;
    int radius;
    int x = -1, y = -1;
    while(getline(file, s)) {
        y++;
        x = 0;
        if (s.size() == 1) {
            radius = std::atoi(s.c_str());
        }
        std::vector<char> v;
        for (char c : s) {
            if (c != ' ') {
                if (c == '1') {
                    cur_coordinates.x = x;
                    cur_coordinates.y =y;
                }
                v.push_back(c);
                x++;
            }
        }
        vec.push_back(v);
    }
}

MemoryUnit* exec(Node* u, Memory* m) {
    std::cout << "NodeType: " << u->get_type() << std::endl;
    switch (u->get_type())
    {
        case NodeType::VARLEAF: {
            try {
                return (*m)[dynamic_cast<VarLeaf*>(u)->name];
            }
            catch (const std::exception&) {
                errors.push_back(NameError("Variable with this name does not exist"));
            }
        }
        case NodeType::INTLEAF: {
            try {
                return dynamic_cast<IntLeaf*>(u)->data;
            }
            catch (std::exception& ex) {
                throw ex.what();
            }
        }
        case NodeType::SHORTLEAF: {
            try {
                return dynamic_cast<ShortLeaf*>(u)->data;
            }
            catch (std::exception& ex) {
                throw ex.what();
            }
        }
        case NodeType::BOOLLEAF: {
            try {
                return dynamic_cast<BoolLeaf*>(u)->data;
            }
            catch (std::exception& ex) {
                throw ex.what();
            }
        }
        case NodeType::ADDNODE: {
            auto e1 = exec(dynamic_cast<AddNode*>(u)->left, m);
            auto e2 = exec(dynamic_cast<AddNode*>(u)->right, m);
            return (e1 && e2) ? new MemoryUnit(e1->add(*e2)) : throw SyntaxError("Add must have 2 parameters");
        }
        case NodeType::SUBNODE: {
            auto e1 = exec(dynamic_cast<SubNode*>(u)->left, m);
            auto e2 = exec(dynamic_cast<SubNode*>(u)->right, m);
            return (e1 && e2) ? new MemoryUnit(e1->sub(*e2)) : throw SyntaxError("Sub must have 2 parameters");
        }
        case NodeType::ANDNODE: {
            auto e1 = exec(dynamic_cast<AndNode*>(u)->left, m);
            auto e2 = exec(dynamic_cast<AndNode*>(u)->right, m);
            return (e1 && e2) ? new MemoryUnit(e1->logic_and(*e2)) : throw SyntaxError("And must have 2 parameters");
        }
        case NodeType::NANDNODE: {
            auto e1 = exec(dynamic_cast<NandNode*>(u)->left, m);
            auto e2 = exec(dynamic_cast<NandNode*>(u)->right, m);
            return (e1 && e2) ? new MemoryUnit(e1->logic_nand(*e2)) : throw SyntaxError("Nand must have 2 parameters");
        }
        case NodeType::ORNODE: {
            auto e1 = exec(dynamic_cast<OrNode*>(u)->left, m);
            auto e2 = exec(dynamic_cast<OrNode*>(u)->right, m);
            return (e1 && e2) ? new MemoryUnit(e1->logic_or(*e2)) : throw SyntaxError("Or must have 2 parameters");
        }
        case NodeType::NORNODE: {
            auto e1 = exec(dynamic_cast<NorNode*>(u)->left, m);
            auto e2 = exec(dynamic_cast<NorNode*>(u)->right, m);
            return (e1 && e2) ? new MemoryUnit(e1->logic_nor(*e2)) : throw SyntaxError("Nor must have 2 parameters");
        }
        case NodeType::SMALLERNODE: {
            auto e1 = exec(dynamic_cast<SmallerNode*>(u)->left, m);
            auto e2 = exec(dynamic_cast<SmallerNode*>(u)->right, m);
            return (e1 && e2) ? new MemoryUnit(e1->smaller(*e2)) : throw SyntaxError("Smaller must have 2 parameters");
        }
        case NodeType::LARGERNODE: {
            auto e1 = exec(dynamic_cast<LargerNode*>(u)->left, m);
            auto e2 = exec(dynamic_cast<LargerNode*>(u)->right, m);
            return (e1 && e2) ? new MemoryUnit(e1->larger(*e2)) : throw SyntaxError("Larger must have 2 parameters");
        }
        case NodeType::SETNODE: {
            auto e1 = exec(dynamic_cast<SetNode*>(u)->left, m);
            auto e2 = exec(dynamic_cast<SetNode*>(u)->right, m);
            if ((e1->data->get_type() == Datatypes::VECTOR && e2->data->get_type() != Datatypes::VECTOR) ||
            (e1->data->get_type() != Datatypes::VECTOR && e2->data->get_type() == Datatypes::VECTOR)) {
                throw TypeError("Types of lvalue and rvalue must be equal");
            }
            return (e1 && e2) ? new MemoryUnit(e1->set(*e2)) : throw SyntaxError("Set must have lvalue and rvalue");
        }
        case NodeType::SIZEOFNODE: {
            auto e1 = exec(dynamic_cast<SizeofNode*>(u)->next, m);
            return (e1) ? new MemoryUnit(e1->size_of()) : throw SyntaxError("Sizeof must have variable or type");
        }
        case NodeType::IFNODE: {
            auto i = dynamic_cast<IfNode*>(u);
            u->local = new Memory(m);
            auto e = exec(i->condition, m);
            if (e) {
                if ((bool)e->data) {
                    exec(i->if_code, u->local);
                }
                else if (i->else_code) {
                    exec(i->else_code, u->local);
                }
                u->local->clear();
                return nullptr;
            }
            else {
                throw SyntaxError("Invalid if condition");
            }
        }
        case NodeType::LOOPNODE: {
            u->local = new Memory(m);
            try {
                while ((bool)exec(dynamic_cast<LoopNode*>(u)->condition, u->local)->data) {
                    exec(dynamic_cast<LoopNode*>(u)->code, u->local);
                }
                u->local->clear();
                return nullptr;
            }
            catch (const CastError& c) {
                throw c;
            }
        }
        case NodeType::VARDECLNODE: {
            auto v = dynamic_cast<VarDeclNode*>(u);
            try {
                m->add(v->var);
                if (v->init) {
                    auto i = exec(v->init, m);
                    if(i) {
                        v->var = new VariableUnit(v->name, i);
                    }
                    else {
                        throw SyntaxError("Declaration must have rvalue");
                    }
                }
            } catch (std::exception ex) {
                throw ex;
            }
        }
        case NodeType::VARLIST: {
            auto v = dynamic_cast<VarListNode*>(u);
            try {
                for (auto it : v->vec) {
                    exec(it, m);
                }
            } catch (std::exception ex) {
                throw ex;
            }
        }
        case NodeType::FDECLNODE: {
            auto f = dynamic_cast<FDeclNode*>(u);
            m->add(f->func);
            u->local = m;
            return nullptr;
        }
        case NodeType::VECDECLNODE: {
            u->local =  m;
            auto vecn = dynamic_cast<VecDeclNode*>(u);
            std::vector<int> tmp;
            auto elems = vecn->elems;
            auto dims = vecn->dims;
            try {
                if (!elems.empty() && !dims.empty()) {
                    if (vecn->vecof_count != dims.size()) {
                        throw SyntaxError("The number of VECTOR OF must be equivalent to nesting the vector");
                    }
                    vecn->init(elems, m);
                    std::vector<int> tmp;
                    for (auto d : dims) {
                        auto s = exec(d, m);
                        if (!s) {
                            throw SyntaxError("Error in initialization");
                        }
                        tmp.push_back((int)*(s->data));
                    }
                    if (vecn->real_dims != tmp) {
                        throw SyntaxError("Error in initialization");
                    }
                    auto vec = new Vector(tmp, vecn->objects);
                    auto var = new VariableUnit(vecn->name, vec);

                } else if (elems.empty() && !dims.empty()) {
                    std::vector<int> tmp;
                    for (auto d : dims) {
                        auto s = exec(d, m);
                        if (!s) {
                            throw SyntaxError("Error in initialization");
                        }
                        tmp.push_back((int)*(s->data));
                    }
                    auto vec = new Vector(tmp);
                    auto var = new VariableUnit(vecn->name, vec);
                } else if (!elems.empty() && dims.empty()) {
                    if (vecn->vecof_count != dims.size()) {
                        throw SyntaxError("The number of VECTOR OF must be equivalent to nesting the vector");
                    }
                    vecn->init(elems, m);
                    auto vec = new Vector(vecn->objects);
                    auto var = new VariableUnit(vecn->name, vec);
                } else {
                    throw SyntaxError("Either a size field or a field for setting values is required");
                }
            } catch (std::exception ex) {
                throw ex;
            }
        }
        case NodeType::FCALLNODE: {
            try {
                std::vector<MemoryUnit*> tmp;
                auto f = dynamic_cast<FcallNode*>(u);
                for (auto p : f->params) {
                    if (p) {
                        auto q = exec(p, m);
                        if (q)
                            tmp.push_back(q);
                        else
                            throw TypeError("It's not a parametr");
                    }
                    else
                        throw TypeError("It's not a parametr");
                }
                auto fnode = dynamic_cast<FunctionUnit*>((*m)[f->name]);
                if (fnode->params.size() != f->params.size()) {
                    throw SyntaxError("Parameters more or less than required");
                }
                auto* local = new Memory(m);
                for (int i = 0; i < fnode->params.size(); i++) {
                    if (fnode->params[i].first != tmp[i]->data->get_type()) {
                        throw TypeError("Type mismatch");
                    }
                    std::pair<std::string, std::shared_ptr<MemoryUnit>> p;
                    auto alloc = new VariableUnit(fnode->params[i].second, tmp[i]);
                    local->add(alloc);
                }
                auto fdecl = dynamic_cast<FDeclNode*>(fnode->link);
                MemoryUnit* tmp1;
                if (fdecl->code) {
                    exec(fdecl->code, local);
                }
                if (fdecl->ret) {
                    tmp1 = exec(fdecl->ret, local);
                    local->clear();
                    return tmp1;
                } else {
                    throw SyntaxError("Return mismatch");
                }
            } catch (std::exception ex) {
                throw ex;
            }
        }
        case NodeType::INDEXNODE: {
            auto i = dynamic_cast<IndexNode*>(u);
            auto v = exec(i->next, m);
            if (!v) {
                throw SyntaxError("Incorrect vector");
            }
            std::vector<int> tmp;
            for (auto p : i->elems) {
                auto t = exec(p, m);
                if (t)
                    tmp.push_back((int)*(t->data));
                else
                    throw SyntaxError("Incorrect path in vector");
            }
            return new MemoryUnit((*v)[tmp]);
        }
        case NodeType::STATEMENT: {
            for (auto v : dynamic_cast<StatementList*>(u)->vec)
                exec(v, m);
            return nullptr;
        }
        case NodeType::RIGHTNODE: {
            int new_x;
            int new_y;
            if (cur_coordinates.y % 2 == 0 && cur_coordinates.x != labirint[0].size()-1) {
                new_x = cur_coordinates.x + 1;
                new_y = cur_coordinates.y + 1;
                if (labirint[new_y][new_x] != "0") {
                    cur_coordinates.x = new_x;
                    cur_coordinates.y = new_y;
                    return new MemoryUnit(new Short(1));
                }
            } else if (cur_coordinates.y % 2 != 0 && cur_coordinates.x != labirint[0].size()-1) {
                new_x = cur_coordinates.x;
                new_y = cur_coordinates.y - 1;
                if (labirint[new_y][new_x] != "0") {
                    cur_coordinates.x = new_x;
                    cur_coordinates.y = new_y;
                    return new MemoryUnit(new Short(1));
                }
            }
            return new MemoryUnit(new Bool(UNDEFINED));
        }
        case NodeType::LEFTNODE: {
            int new_x;
            int new_y;
            if (cur_coordinates.y % 2 == 0 && cur_coordinates.x != 0) {
                new_x = cur_coordinates.x + 1;
                new_y = cur_coordinates.y + 1;
                if (labirint[new_y][new_x] != "0") {
                    cur_coordinates.x = new_x;
                    cur_coordinates.y = new_y;
                    return new MemoryUnit(new Short(-1));
                }
            } else if (cur_coordinates.y % 2 != 0 && cur_coordinates.x != 0) {
                new_x = cur_coordinates.x + 1;
                new_y = cur_coordinates.y - 1;
                if (labirint[new_y][new_x] != "0") {
                    cur_coordinates.x = new_x;
                    cur_coordinates.y = new_y;
                    return new MemoryUnit(new Short(-1));
                }
            }
            return new MemoryUnit(new Bool(UNDEFINED));
        }
        case NodeType::MOVENODE: {
            int new_x;
            int new_y;
            if (cur_coordinates.y % 2 == 0 && cur_coordinates.y != 0) {
                new_x = cur_coordinates.x;
                new_y = cur_coordinates.y - 1;
                if (labirint[new_y][new_x] != "0") {
                    cur_coordinates.x = new_x;
                    cur_coordinates.y = new_y;
                    return new MemoryUnit(new Short(1));
                }
            } else if (cur_coordinates.y % 2 != 0 && cur_coordinates.x != labirint.size()-1) {
                new_x = cur_coordinates.x ;
                new_y = cur_coordinates.y + 1;
                if (labirint[new_y][new_x] != "0") {
                    cur_coordinates.x = new_x;
                    cur_coordinates.y = new_y;
                    return new MemoryUnit(new Short(-1));
                }
            }
            return new MemoryUnit(new Bool(UNDEFINED));
        }
        case NodeType::LMSNODE : {
            coordinates tmp_coordinates;
            int left = 0, right = 0;
            tmp_coordinates.x = cur_coordinates.x; tmp_coordinates.y = cur_coordinates.y;
            int new_x = tmp_coordinates.y,  new_y = tmp_coordinates.x;
            bool finish_left = false, finish_right = false;
            while (labirint[new_y][new_x] != "0") {
                if (tmp_coordinates.y % 2 == 0 && tmp_coordinates.x != 0) {
                    new_x = tmp_coordinates.x + 1;
                    new_y = tmp_coordinates.y + 1;
                    if (labirint[new_y][new_x] == "3") {
                        finish_left = true;
                        break;
                    }
                    if (labirint[new_y][new_x] != "0") {
                        tmp_coordinates.x = new_x;
                        tmp_coordinates.y = new_y;
                        left++;
                    }
                } else if (tmp_coordinates.y % 2 != 0 && tmp_coordinates.x != 0) {
                    new_x = tmp_coordinates.x + 1;
                    new_y = tmp_coordinates.y - 1;
                    if (labirint[new_y][new_x] == "3") {
                        finish_left = true;
                        break;
                    }
                    if (labirint[new_y][new_x] != "0") {
                        tmp_coordinates.x = new_x;
                        tmp_coordinates.y = new_y;
                        left++;
                    }
                }
            }
            tmp_coordinates.x = cur_coordinates.x; tmp_coordinates.y = cur_coordinates.y;
            new_x = tmp_coordinates.y, new_y = tmp_coordinates.x;
            while (labirint[new_y][new_x] != "0") {
                if (tmp_coordinates.y % 2 == 0 && tmp_coordinates.x != 0) {
                    new_x = tmp_coordinates.x + 1;
                    new_y = tmp_coordinates.y + 1;
                    if (labirint[new_y][new_x] == "3") {
                        finish_right = true;
                        break;
                    }
                    if (labirint[new_y][new_x] != "0") {
                        tmp_coordinates.x = new_x;
                        tmp_coordinates.y = new_y;
                        right++;
                    }
                } else if (tmp_coordinates.y % 2 != 0 && tmp_coordinates.x != 0) {
                    new_x = tmp_coordinates.x + 1;
                    new_y = tmp_coordinates.y - 1;
                    if (labirint[new_y][new_x] == "3") {
                        finish_right = true;
                        break;
                    }
                    if (labirint[new_y][new_x] != "0") {
                        tmp_coordinates.x = new_x;
                        tmp_coordinates.y = new_y;
                        right++;
                    }
                }
            }
            if (finish_left) {
                if (left <= INT16_MAX) {
                    return new MemoryUnit(new Short(left));
                } else {
                    return new MemoryUnit(new Int(left));
                }
            }
            if (finish_right) {
                if (right <= INT16_MAX) {
                    return new MemoryUnit(new Short(-right));
                } else {
                    return new MemoryUnit(new Int(-right));
                }
            }
            if (dynamic_cast<Int*>(side->data)->value == -1) {
                if (left <= INT16_MAX) {
                    return new MemoryUnit(new Short(-left));
                } else {
                    return new MemoryUnit(new Int(-left));
                }
            } else {
                if (right <= INT16_MAX) {
                    return new MemoryUnit(new Short(right));
                } else {
                    return new MemoryUnit(new Int(right));
                }
            }
            dynamic_cast<Int*>(side->data)->value *= -1;
            //            if (finish_left) {
            //                if (right <= INT16_MAX) {
            //                    return std::make_shared<MemoryUnit>(std::make_shared<Short>(right));
            //                } else {
            //                    return std::make_shared<MemoryUnit>(std::make_shared<Int>(right));
            //                }
            //            }
            //            if (finish_right) {
            //                if (left <= INT16_MAX) {
            //                    return std::make_shared<MemoryUnit>(std::make_shared<Short>(left));
            //                } else {
            //                    return std::make_shared<MemoryUnit>(std::make_shared<Int>(left));
            //                }
            //            }
            //            if (left > right && left <= radius) {
            //                if (left <= INT16_MAX) {
            //                    return std::make_shared<MemoryUnit>(std::make_shared<Short>(-1*left));
            //                } else {
            //                    return std::make_shared<MemoryUnit>(std::make_shared<Int>(-1*left));
            //                }
            //            } else {
            //                return std::make_shared<MemoryUnit>(std::make_shared<Short>(0));
            //            }
            //            if (left < right && right <= radius) {
            //                if (right <= INT16_MAX) {
            //                    return std::make_shared<MemoryUnit>(std::make_shared<Short>(right));
            //                } else {
            //                    return std::make_shared<MemoryUnit>(std::make_shared<Int>(right));
            //                }
            //            } else {
            //                return std::make_shared<MemoryUnit>(std::make_shared<Short>(0));
            //            }
        }
        case NodeType::PRINTNODE: {
            auto d = exec(dynamic_cast<PrintNode*>(u)->next, m)->data;
            if (d->get_type() == Datatypes::INT) {
                std::cout << dynamic_cast<Int*>(d)->value << std::endl;
            } else if (d->get_type() == Datatypes::SHORT) {
                std::cout << dynamic_cast<Short*>(d)->value << std::endl;
            } else if (d->get_type() == Datatypes::BOOL) {
                auto v = dynamic_cast<Bool*>(d)->value;
                if (v == Logic::TRUE) {
                    std::cout << "true" << std::endl;
                } else if (v == Logic::FALSE) {
                    std::cout << "false" << std::endl;
                } else {
                    std::cout << "undefined" << std::endl;
                }
            } else {
                auto v = dynamic_cast<Vector*>(d);
                for (int i = 0; i < v->count; i++) {
                    if (v->vec[i]->get_type() == Datatypes::INT) {
                        std::cout << dynamic_cast<Int*>(v->vec[i])->value << std::endl;
                    } else if (v->vec[i]->get_type() == Datatypes::SHORT) {
                        std::cout << dynamic_cast<Short*>(v->vec[i])->value << std::endl;
                    } else if (v->vec[i]->get_type() == Datatypes::BOOL) {
                        auto b = dynamic_cast<Bool*>(v->vec[i])->value;
                        if (b == Logic::TRUE) {
                            std::cout << "true" << std::endl;
                        } else if (b == Logic::FALSE) {
                            std::cout << "false" << std::endl;
                        } else {
                            std::cout << "undefined" << std::endl;
                        }
                    }
                }
            }
            return nullptr;
        }
        default:
            break;
    }
}

