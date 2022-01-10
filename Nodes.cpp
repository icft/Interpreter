#include "Nodes.h"

typedef struct {
    int x;
    int y;
} coordinates;

std::vector<std::vector<std::string>> labirint; //0-тупик, 1-текущее, 2-пустота, 3-выходы
coordinates cur_coordinates;
int radius;


// VarLeaf::VarLeaf(int line, const std::string &s) {
//     line_number = line;
//     name = s;
// }
// 
// NodeType VarLeaf::get_type() {
//     return type;
// }
// 
// IntLeaf::IntLeaf(int line, std::int32_t value) {
//     data = std::make_shared<MemoryUnit>(std::make_shared<Int>(value));
//     line_number = line;
// }
// 
// IntLeaf::IntLeaf(MemoryUnit m) {
//     data = std::make_shared<MemoryUnit>(m);
// }
// 
// NodeType IntLeaf::get_type() {
//     return type;
// }
// 
// ShortLeaf::ShortLeaf(MemoryUnit m) {
//     data = std::make_shared<MemoryUnit>(m);
// }
// 
// ShortLeaf::ShortLeaf(int line, std::int16_t value) {
//     data = std::make_shared<MemoryUnit>(std::make_shared<Short>(value));
//     line_number = line;
// }
// 
// NodeType ShortLeaf::get_type() {
//     return type;
// }
// 
// BoolLeaf::BoolLeaf(MemoryUnit m) {
//     data = std::make_shared<MemoryUnit>(m);
// }
// 
// BoolLeaf::BoolLeaf(int line, Logic value) {
//     data = std::make_shared<MemoryUnit>(std::make_shared<Bool>(value));
//     line_number = line;
// }
// 
// NodeType BoolLeaf::get_type() {
//     return type;
// }
// 
// AddNode::AddNode(int line, const std::shared_ptr<Node> &l, const std::shared_ptr<Node> &r) {
//     if (l && r) {
//         line_number = line;
//         left = l;
//         right = r;
//     }
//     else {
//         throw SyntaxError("Add must have 2 parameters");
//     }
// }
// 
// NodeType AddNode::get_type() {
//     return type;
// }
// 
// SubNode::SubNode(int line, const std::shared_ptr<Node> &l, const std::shared_ptr<Node> &r) {
//     if (l && r) {
//         line_number = line;
//         left = l;
//         right = r;
//     }
//     else {
//         throw SyntaxError("Sub must have 2 parameters");
//     }
// }
// 
// NodeType SubNode::get_type() {
//     return type;
// }
// 
// AndNode::AndNode(int line, const std::shared_ptr<Node> &l, const std::shared_ptr<Node> &r) {
//     if (l && r) {
//         line_number = line;
//         left = l;
//         right = r;
//     }
//     else {
//         throw SyntaxError("And must have 2 parameters");
//     }
// }
// 
// NodeType AndNode::get_type() {
//     return type;
// }
// 
// NandNode::NandNode(int line, const std::shared_ptr<Node> &l, const std::shared_ptr<Node> &r) {
//     if (l && r) {
//         line_number = line;
//         left = l;
//         right = r;
//     }
//     else {
//         throw SyntaxError("Nand must have 2 parameters");
//     }
// }
// 
// NodeType NandNode::get_type() {
//     return type;
// }
// 
// OrNode::OrNode(int line, const std::shared_ptr<Node> &l, const std::shared_ptr<Node> &r) {
//     if (l && r) {
//         left = l;
//         right = r;
//     }
//     else {
//         throw SyntaxError("Or must have 2 parameters");
//     }
// }
// 
// NodeType OrNode::get_type() {
//     return type;
// }
// 
// NorNode::NorNode(int line, const std::shared_ptr<Node> &l, const std::shared_ptr<Node> &r) {
//     if (l && r) {
//         line_number = line;
//         left = l;
//         right = r;
//     }
//     else {
//         throw SyntaxError("Nor must have 2 parameters");
//     }
// }
// 
// NodeType NorNode::get_type() {
//     return type;
// }
// 
// SmallerNode::SmallerNode(int line, const std::shared_ptr<Node> &l, const std::shared_ptr<Node> &r) {
//     if (l && r) {
//         line_number = line;
//         left = l;
//         right = r;
//     }
//     else {
//         throw SyntaxError("Smaller must have 2 parameters");
//     }
// }
// 
// NodeType SmallerNode::get_type() {
//     return type;
// }
// 
// LargerNode::LargerNode(int line, const std::shared_ptr<Node> &l, const std::shared_ptr<Node> &r) {
//     if (l && r) {
//         line_number = line;
//         left = l;
//         right = r;
//     }
//     else {
//         throw SyntaxError("Larger must have 2 parameters");
//     }
// }
// 
// NodeType LargerNode::get_type() {
//     return type;
// }
// 
// SetNode::SetNode(int line, const std::shared_ptr<Node> &l, const std::shared_ptr<Node> &r) {
//     if (l && r) {
//         line_number = line;
//         left = l;
//         right = r;
//     }
//     else {
//         throw SyntaxError("Set must have lvalue and rvalue");
//     }
// }
// 
// LoopNode::LoopNode(int line, std::shared_ptr<Node> cond, std::shared_ptr<Node> c) {
//     if (cond == nullptr) {
//         throw SyntaxError("Loop must have  a condition");
//     }
//     else {
//         line_number = line;
//         condition = cond;
//         code = c;
//     }
// }
// 
// NodeType LoopNode::get_type() {
//     return type;
// }
// 
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
// 
// NodeType FDeclNode::get_type() {
//     return type;
// }
// 
// FcallNode::FcallNode(int line, std::string n, std::vector<std::shared_ptr<Node>> p) : name(n), params(p) {
//     line_number = line;
// }
// 
// NodeType FcallNode::get_type() {
//     return type;
// }
// 
// SizeofNode::SizeofNode(int line, Datatypes t) {
//     if ( t == Datatypes::INT) {
//         line_number = line;
//         next = std::make_shared<IntLeaf>(MemoryUnit(std::make_shared<Int>()));
//     } else if (t == Datatypes::SHORT) {
//         line_number = line;
//         next = std::make_shared<IntLeaf>(MemoryUnit(std::make_shared<Short>()));
//     } else if (t ==Datatypes::BOOL) {
//         line_number = line;
//         next = std::make_shared<IntLeaf>(MemoryUnit(std::make_shared<Bool>()));
//     } else {
//         throw SyntaxError("Can't be computed for a vector");
//     }
// }
// 
// SizeofNode::SizeofNode(int line, std::string n) {
//     line_number = line;
//     next = std::make_shared<VarLeaf>(line, n);
// }
// 
// NodeType SizeofNode::get_type() {
//     return type;
// }
// 
// IfNode::IfNode(int line, std::shared_ptr<Node> c, std::shared_ptr<Node> i, std::shared_ptr<Node> e) {
//     if (c) {
//         line_number = line;
//         condition = c;
//         if_code = i;
//         else_code = e;
//     }
//     else {
//         throw SyntaxError("If must have a condition");
//     }
// }
// 
// NodeType IfNode::get_type() {
//     return type;
// }
// 
// VecDeclNode::VecDeclNode(int line, int v, std::string n, std::vector<std::shared_ptr<Node>> e,
//                          std::vector<std::shared_ptr<Node>> d) : vecof_count(v), name(n), elems(e), dims(d), main(true) {
//     line_number = line;
// }
// 
// VecDeclNode::VecDeclNode(int line, std::vector<std::shared_ptr<Node>> e) : elems(e) {
//     name = {}; dims = {}; vecof_count = {}; main = false;
//     line_number = line;
// }
// 
// void VecDeclNode::init(std::vector<std::shared_ptr<Node>> v, std::shared_ptr<Memory> m) {
//     std::pair<int, std::vector<Object>> p;
//     auto k = false;
//     auto s = 0;
//     for (auto it = v.begin(); it != v.end(); it++) {
//         if ((*it)->get_type() == NodeType::VECDECLNODE) {
//             if (it == v.begin()) {
//                 s = std::dynamic_pointer_cast<VecDeclNode>(*it)->elems.size();
//             } else {
//                 if (s != std::dynamic_pointer_cast<VecDeclNode>(*it)->elems.size()) {
//                     throw SyntaxError("Different sizes");
//                 }
//             }
//             init(std::dynamic_pointer_cast<VecDeclNode>(*it)->elems, m);
//             k = true;
//         } else if (k && (*it)->get_type() != NodeType::VECDECLNODE) {
//             throw SyntaxError("Vector error");
//         } else if (it != v.begin() && !k && (*it)->get_type() != NodeType::VECDECLNODE) {
//             throw SyntaxError("Vector error");
//         } else {
//             auto n = exec(*it, m);
//             if (!n) {
//                 throw SyntaxError("Error in initialization");
//             }
//             objects.push_back(n->data);
//         }
//     }
//     if (k) {
//         real_dims.push_back(s);
//     }
// }
// 
// NodeType VecDeclNode::get_type() {
//     return type;
// }
// 
// IndexNode::IndexNode(int line, std::shared_ptr<Node> n, std::vector<std::shared_ptr<Node>> e) : next(n), elems(e) {
//     if (!next) {
//         throw SyntaxError("Vector missed");
//     }
//     line_number = line;
// }
// 
// NodeType IndexNode::get_type() {
//     return type;
// }
// 
// VarDeclNode::VarDeclNode(int line, std::string n, Datatypes t, std::shared_ptr<Node> init_node) {
//     line_number = line;
//     std::shared_ptr<Object> obj;
//     if (t == Datatypes::INT) {
//         obj = std::make_shared<Int>();
//     }
//     else if (t == Datatypes::SHORT) {
//         obj = std::make_shared<Short>();
//     }
//     else {
//         obj = std::make_shared<Bool>();
//     }
//     var = std::make_shared<VariableUnit>(n, obj);
//     init = init_node;
// }
// 
// VarDeclNode::VarDeclNode(std::string n, std::shared_ptr<MemoryUnit> m) {
//     name = n;
//     var = std::make_shared<VariableUnit>(n, m);
// }
// 
// NodeType VarDeclNode::get_type() {
//     return type;
// }
// 
// VarListNode::VarListNode(int line, std::pair<Datatypes, std::vector<VarDeclaration>> p) {
//     t = p.first;
//     line_number = line;
//     for (auto it : p.second) {
//         auto e = std::make_shared<VarDeclNode>(line, it.name, t, it.init);
//         vec.push_back(e);
//     }
// }
// 
// StatementList::StatementList(std::shared_ptr<Node> n) {
//     if (n)
//         vec.push_back(n);
// }
// 
// void StatementList::add(std::shared_ptr<Node> n) {
//     if (n)
//         vec.push_back(n);
// }
// 
// NodeType RightNode::get_type() {
//     return type;
// }
// 
// NodeType LeftNode::get_type() {
//     return type;
// }
// 
// NodeType MoveNode::get_type() {
//     return type;
// }
// 
// NodeType LmsNode::get_type() {
//     return type;
// }

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

void init_memory(std::shared_ptr<Node> n) {
    n->local = std::shared_ptr<Memory>();
}

std::shared_ptr<MemoryUnit> exec(std::shared_ptr<Node> u, std::shared_ptr<Memory> m) {
    switch (u->get_type())
    {
        case NodeType::VARLEAF: {
            try {
                return (*m)[std::dynamic_pointer_cast<VarLeaf>(u)->name];
            }
            catch (const std::exception&) {
                throw NameError("Variable with this name does not exist");
            }
        }
        case NodeType::INTLEAF: {
            try {
                return std::dynamic_pointer_cast<IntLeaf>(u)->data;
            }
            catch (std::exception& ex) {
                throw ex.what();
            }
        }
        case NodeType::SHORTLEAF: {
            try {
                return std::dynamic_pointer_cast<ShortLeaf>(u)->data;
            }
            catch (std::exception& ex) {
                throw ex.what();
            }
        }
        case NodeType::BOOLLEAF: {
            try {
                return std::dynamic_pointer_cast<BoolLeaf>(u)->data;
            }
            catch (std::exception& ex) {
                throw ex.what();
            }
        }
        case NodeType::ADDNODE: {
            auto e1 = exec(std::dynamic_pointer_cast<AddNode>(u)->left, m);
            auto e2 = exec(std::dynamic_pointer_cast<AddNode>(u)->right, m);
            return (e1 && e2) ? std::make_shared<MemoryUnit>(e1->add(*e2)) : throw SyntaxError("Add must have 2 parameters");
        }
        case NodeType::SUBNODE: {
            auto e1 = exec(std::dynamic_pointer_cast<SubNode>(u)->left, m);
            auto e2 = exec(std::dynamic_pointer_cast<SubNode>(u)->right, m);
            return (e1 && e2) ? std::make_shared<MemoryUnit>(e1->sub(*e2)) : throw SyntaxError("Sub must have 2 parameters");
        }
        case NodeType::ANDNODE: {
            auto e1 = exec(std::dynamic_pointer_cast<AndNode>(u)->left, m);
            auto e2 = exec(std::dynamic_pointer_cast<AndNode>(u)->right, m);
            return (e1 && e2) ? std::make_shared<MemoryUnit>(e1->logic_and(*e2)) : throw SyntaxError("And must have 2 parameters");
        }
        case NodeType::NANDNODE: {
            auto e1 = exec(std::dynamic_pointer_cast<NandNode>(u)->left, m);
            auto e2 = exec(std::dynamic_pointer_cast<NandNode>(u)->right, m);
            return (e1 && e2) ? std::make_shared<MemoryUnit>(e1->logic_nand(*e2)) : throw SyntaxError("Nand must have 2 parameters");
        }
        case NodeType::ORNODE: {
            auto e1 = exec(std::dynamic_pointer_cast<OrNode>(u)->left, m);
            auto e2 = exec(std::dynamic_pointer_cast<OrNode>(u)->right, m);
            return (e1 && e2) ? std::make_shared<MemoryUnit>(e1->logic_or(*e2)) : throw SyntaxError("Or must have 2 parameters");
        }
        case NodeType::NORNODE: {
            auto e1 = exec(std::dynamic_pointer_cast<NorNode>(u)->left, m);
            auto e2 = exec(std::dynamic_pointer_cast<NorNode>(u)->right, m);
            return (e1 && e2) ? std::make_shared<MemoryUnit>(e1->logic_nor(*e2)) : throw SyntaxError("Nor must have 2 parameters");
        }
        case NodeType::SMALLERNODE: {
            auto e1 = exec(std::dynamic_pointer_cast<SmallerNode>(u)->left, m);
            auto e2 = exec(std::dynamic_pointer_cast<SmallerNode>(u)->right, m);
            return (e1 && e2) ? std::make_shared<MemoryUnit>(e1->smaller(*e2)) : throw SyntaxError("Smaller must have 2 parameters");
        }
        case NodeType::LARGERNODE: {
            auto e1 = exec(std::dynamic_pointer_cast<LargerNode>(u)->left, m);
            auto e2 = exec(std::dynamic_pointer_cast<LargerNode>(u)->right, m);
            return (e1 && e2) ? std::make_shared<MemoryUnit>(e1->larger(*e2)) : throw SyntaxError("Larger must have 2 parameters");
        }
        case NodeType::SETNODE: {
            auto e1 = exec(std::dynamic_pointer_cast<SetNode>(u)->left, m);
            auto e2 = exec(std::dynamic_pointer_cast<SetNode>(u)->right, m);
            if ((e1->data->get_type() == Datatypes::VECTOR && e2->data->get_type() != Datatypes::VECTOR) ||
            (e1->data->get_type() != Datatypes::VECTOR && e2->data->get_type() == Datatypes::VECTOR)) {
                throw TypeError("Types of lvalue and rvalue must be equal");
            }
            return (e1 && e2) ? std::make_shared<MemoryUnit>(e1->set(*e2)) : throw SyntaxError("Set must have lvalue and rvalue");
        }
        case NodeType::SIZEOFNODE: {
            auto e1 = exec(std::dynamic_pointer_cast<SizeofNode>(u)->next, m);
            return (e1) ? std::make_shared<MemoryUnit>(e1->size_of()) : throw SyntaxError("Sizeof must have variable or type");
        }
        case NodeType::IFNODE: {
            auto i = std::dynamic_pointer_cast<IfNode>(u);
            u->local = std::make_shared<Memory>(m);
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
            u->local = std::make_shared<Memory>(m);
            try {
                while ((bool)exec(std::dynamic_pointer_cast<LoopNode>(u)->condition, u->local)->data) {
                    exec(std::dynamic_pointer_cast<LoopNode>(u)->code, u->local);
                }
                u->local->clear();
                return nullptr;
            }
            catch (const CastError& c) {
                throw c;
            }
        }
        case NodeType::VARDECLNODE: {
            auto v = std::dynamic_pointer_cast<VarDeclNode>(u);
            try {
                m->add(v->var);
                if (v->init) {
                    auto i = exec(v->init, m);
                    if(i) {
                        v->var = std::make_shared<VariableUnit>(v->name, i);
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
            auto v = std::dynamic_pointer_cast<VarListNode>(u);
            try {
                for (auto it : v->vec) {
                    exec(it, m);
                }
            } catch (std::exception ex) {
                throw ex;
            }
        }
        case NodeType::FDECLNODE: {
            auto f = std::dynamic_pointer_cast<FDeclNode>(u);
            m->add(f->func);
            u->local = m;
            return nullptr;
        }
        case NodeType::VECDECLNODE: {
            u->local =  m;
            auto vecn = std::dynamic_pointer_cast<VecDeclNode>(u);
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
                    auto vec = std::make_shared<Vector>(tmp, vecn->objects);
                    auto var = std::make_shared<VariableUnit>(vecn->name, vec);

                } else if (elems.empty() && !dims.empty()) {
                    std::vector<int> tmp;
                    for (auto d : dims) {
                        auto s = exec(d, m);
                        if (!s) {
                            throw SyntaxError("Error in initialization");
                        }
                        tmp.push_back((int)*(s->data));
                    }
                    auto vec = std::make_shared<Vector>(tmp);
                    auto var = std::make_shared<VariableUnit>(vecn->name, vec);
                } else if (!elems.empty() && dims.empty()) {
                    if (vecn->vecof_count != dims.size()) {
                        throw SyntaxError("The number of VECTOR OF must be equivalent to nesting the vector");
                    }
                    vecn->init(elems, m);
                    auto vec = std::make_shared<Vector>(vecn->objects);
                    auto var = std::make_shared<VariableUnit>(vecn->name, vec);
                } else {
                    throw SyntaxError("Either a size field or a field for setting values is required");
                }
            } catch (std::exception ex) {
                throw ex;
            }
        }
        case NodeType::FCALLNODE: {
            try {
                std::vector<std::shared_ptr<MemoryUnit>> tmp;
                auto f = std::dynamic_pointer_cast<FcallNode>(u);
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
                auto fnode = std::dynamic_pointer_cast<FunctionUnit>((*m)[f->name]);
                if (fnode->params.size() != f->params.size()) {
                    throw SyntaxError("Parameters more or less than required");
                }
                std::shared_ptr<Memory> local = std::make_shared<Memory>(m);
                for (int i = 0; i < fnode->params.size(); i++) {
                    if (fnode->params[i].first != tmp[i]->data->get_type()) {
                        throw TypeError("Type mismatch");
                    }
                    std::pair<std::string, std::shared_ptr<MemoryUnit>> p;
                    auto alloc = std::make_shared<VariableUnit>(fnode->params[i].second, tmp[i]);
                    local->add(alloc);
                }
                auto fdecl = std::dynamic_pointer_cast<FDeclNode>(fnode->link);
                std::shared_ptr<MemoryUnit> tmp1;
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
            auto i = std::dynamic_pointer_cast<IndexNode>(u);
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
            return std::make_shared<MemoryUnit>((*v)[tmp]);
        }
        case NodeType::STATEMENT: {
            for (auto v : std::dynamic_pointer_cast<StatementList   >(u)->vec)
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
                    return std::make_shared<MemoryUnit>(std::make_shared<Short>(1));
                }
            } else if (cur_coordinates.y % 2 != 0 && cur_coordinates.x != labirint[0].size()-1) {
                new_x = cur_coordinates.x;
                new_y = cur_coordinates.y - 1;
                if (labirint[new_y][new_x] != "0") {
                    cur_coordinates.x = new_x;
                    cur_coordinates.y = new_y;
                    return std::make_shared<MemoryUnit>(std::make_shared<Short>(1));
                }
            }
            return std::make_shared<MemoryUnit>(std::make_shared<Bool>(UNDEFINED));
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
                    return std::make_shared<MemoryUnit>(std::make_shared<Short>(-1));
                }
            } else if (cur_coordinates.y % 2 != 0 && cur_coordinates.x != 0) {
                new_x = cur_coordinates.x + 1;
                new_y = cur_coordinates.y - 1;
                if (labirint[new_y][new_x] != "0") {
                    cur_coordinates.x = new_x;
                    cur_coordinates.y = new_y;
                    return std::make_shared<MemoryUnit>(std::make_shared<Short>(-1));
                }
            }
            return std::make_shared<MemoryUnit>(std::make_shared<Bool>(UNDEFINED));
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
                    return std::make_shared<MemoryUnit>(std::make_shared<Short>(1));
                }
            } else if (cur_coordinates.y % 2 != 0 && cur_coordinates.x != labirint.size()-1) {
                new_x = cur_coordinates.x ;
                new_y = cur_coordinates.y + 1;
                if (labirint[new_y][new_x] != "0") {
                    cur_coordinates.x = new_x;
                    cur_coordinates.y = new_y;
                    return std::make_shared<MemoryUnit>(std::make_shared<Short>(-1));
                }
            }
            return std::make_shared<MemoryUnit>(std::make_shared<Bool>(UNDEFINED));
        }
        case NodeType::LMSNODE : {
            coordinates tmp_coordinates;
            int left = 0, right = 0;
            tmp_coordinates.x = cur_coordinates.x; tmp_coordinates.y = cur_coordinates.y;
            int new_x = tmp_coordinates.y,  new_y = tmp_coordinates.x;
            bool finish_left = false, finish_right = false;;
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
                if (right <= INT16_MAX) {
                    return std::make_shared<MemoryUnit>(std::make_shared<Short>(right));
                } else {
                    return std::make_shared<MemoryUnit>(std::make_shared<Int>(right));
                }
            }
            if (finish_right) {
                if (left <= INT16_MAX) {
                    return std::make_shared<MemoryUnit>(std::make_shared<Short>(left));
                } else {
                    return std::make_shared<MemoryUnit>(std::make_shared<Int>(left));
                }
            }
            if (left > right && left <= radius) {
                if (left <= INT16_MAX) {
                    return std::make_shared<MemoryUnit>(std::make_shared<Short>(-1*left));
                } else {
                    return std::make_shared<MemoryUnit>(std::make_shared<Int>(-1*left));
                }
            } else {
                return std::make_shared<MemoryUnit>(std::make_shared<Bool>(UNDEFINED));
            }
            if (left < right && right <= radius) {
                if (right <= INT16_MAX) {
                    return std::make_shared<MemoryUnit>(std::make_shared<Short>(right));
                } else {
                    return std::make_shared<MemoryUnit>(std::make_shared<Int>(right));
                }
            } else {
                return std::make_shared<MemoryUnit>(std::make_shared<Bool>(UNDEFINED));
            }
        }
        case NodeType::PRINTNODE: {
            auto d = exec(std::dynamic_pointer_cast<PrintNode>(u)->next, m)->data;
            if (d->get_type() == Datatypes::INT) {
                std::cout << std::dynamic_pointer_cast<Int>(d)->value << std::endl;
            } else if (d->get_type() == Datatypes::SHORT) {
                std::cout << std::dynamic_pointer_cast<Short>(d)->value << std::endl;
            } else if (d->get_type() == Datatypes::BOOL) {
                auto v = std::dynamic_pointer_cast<Bool>(d)->value;
                if (v == Logic::TRUE) {
                    std::cout << "true" << std::endl;
                } else if (v == Logic::FALSE) {
                    std::cout << "false" << std::endl;
                } else {
                    std::cout << "undefined" << std::endl;
                }
            } else {
                auto v = std::dynamic_pointer_cast<Vector>(d);
                for (int i = 0; i < v->count; i++) {
                    if (v->vec[i]->get_type() == Datatypes::INT) {
                        std::cout << std::dynamic_pointer_cast<Int>(v->vec[i])->value << std::endl;
                    } else if (v->vec[i]->get_type() == Datatypes::SHORT) {
                        std::cout << std::dynamic_pointer_cast<Short>(v->vec[i])->value << std::endl;
                    } else if (v->vec[i]->get_type() == Datatypes::BOOL) {
                        auto b = std::dynamic_pointer_cast<Bool>(v->vec[i])->value;
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

