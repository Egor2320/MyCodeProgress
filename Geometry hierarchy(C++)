#include <cmath>
#include <vector>
#include <algorithm>

//Vector:
struct vector{
    double x, y;
    vector(double x, double y): x(x), y(y){};

    vector(const vector &other){
        *this = vector();
        x = other.x;
        y = other.y;
    }

    vector() = default;

    vector &operator += (const vector &other){
        this->x += other.x;
        this->y += other.y;
        return *this;
    }

    vector &operator -= (const vector &other){
        this->x -= other.x;
        this->y -= other.y;
        return *this;
    }

    vector &operator *= (const double &a){
        this->x *= a;
        this->y *= a;
        return *this;
    }

    vector &operator /= (const double &a){
        this->x /= a;
        this->y /= a;
        return *this;
    }

    vector operator + ()const{
        auto res = vector(*this);
        return res;
    }

    vector operator-()const{
        auto res = vector(*this);
        res.x *= -1;
        res.y *= -1;
        return res;
    }

    double length()const{
        return std::sqrt((std::pow(x, 2) + std::pow(y, 2)));
    }

};

double dot_product(const vector &v1, const vector &v2){
    return v1.x * v2.x + v1.y * v2.y;
}

double cross_product(const vector &v1, const vector &v2){
    return v1.x * v2.y - v1.y * v2.x;
}

bool collinear(const vector &v1, const vector &v2){
    const double eps = 1e-6;
    return std::abs((v1.x / v2.x) - (v1.y / v2.y)) < eps;
}

double dist(const vector &v1, const vector &v2){
    return std::sqrt((v1.x-v2.x)*(v1.x-v2.x) + (v1.y-v2.y)*(v1.y-v2.y));
}

vector operator + (const vector &v1, const vector &v2){
    auto res = vector(v1);
    res += v2;
    return res;
}

vector operator - (const vector &v1, const vector &v2){
    auto res = vector(v1);
    res -= v2;
    return res;
}

vector operator * (const vector &v1, const double &a){
    auto res = vector(v1);
    res *= a;
    return res;
}

vector operator * (const double &a, const vector &v1){
    auto res = vector(v1);
    res *= a;
    return res;
}

bool operator == (const vector &v1, const vector &v2){
    const double eps = 1e-6;
    return (std::abs(v1.x - v2.x) < eps && std::abs(v1.y - v2.y) < eps);
}

bool operator != (const vector &v1, const vector &v2){
    return !(v1 == v2);
}

vector operator / (const vector &v1, const double &a){
    auto res = vector(v1);
    res /= a;
    return res;
}

//Shape:
class shape{
public:
    virtual vector center()const = 0;
    virtual double perimeter()const = 0;
    virtual double area()const = 0;
    bool operator==(const shape &other)const;
    bool operator!=(const shape &other)const;
    bool congruent_to(const shape& another)const;
    virtual void rotate(double angle) = 0;
    virtual void scale(double coefficient) = 0;
    virtual void translate(vector transform) = 0;
};

//Circle:
class circle : public shape{
    std::vector<double> cent;
    double rad;

public:
    circle(const vector &v, const double &r){
        cent.push_back(v.x);
        cent.push_back(v.y);
        rad = r;
    }

    ~circle() = default;

    vector center()const override{
        auto res = vector(cent[0], cent[1]);
        return res;
    }

    double perimeter()const override{
        return M_PI * 2 * rad;
    }

    double area()const override{
        return M_PI * rad * rad;
    }

    bool operator == (const circle &other)const{
        const double eps = 1e-6;
        return (std::abs(cent[0] - other.cent[0]) < eps && std::abs(cent[1] - other.cent[1]) < eps && std::abs(rad - other.rad) < eps);
    }

    bool operator == (const shape &other)const{
        return false;
    }

    bool operator != (const circle &other) const{
        return !((*this) == other);
    }

    void scale(double coefficient) override{
        rad *= std::abs(coefficient);
    }

    void translate(vector transform)override{
        cent[0] += transform.x;
        cent[1] += transform.y;
    }

    void rotate(double angle)override{}

    bool congruent_to(const circle &other)const{
        const double eps = 1e-6;
        if(std::abs(rad - other.rad) < eps) return true;
        else return false;
    }

    double radius()const{
        return rad;
    }
};

//Polygon:
class polygon : public shape{
    std::vector<vector> vert;

    void sort(){
        size_t n = vertices_count();
        double prd = 0;
        for(size_t i = 0; i < n; ++i){
            prd += cross_product(vert[i%n], vert[(i+1)%n]);
        }
        if(prd <= 0)
            std::reverse(vert.begin(), vert.end());
    }

public:
    explicit polygon(std::vector<vector> vec){
        size_t n = vec.size();
        vert.resize(n);
        for(size_t i = 0; i < n; ++i){
            vert[i] = vec[i];
        }
        sort();
    }

    polygon (const polygon &other){
        *this = polygon(other.get_vertices());
        sort();
    }

    polygon &operator = (const polygon &other){
        vert.clear();
        vert = other.vert;
        sort();
        return *this;
    }

    size_t vertices_count()const{
        return vert.size();
    }

    const std::vector<vector> &get_vertices()const{
        return vert;
    }

    bool operator == (const circle &other)const{
        return false;
    }

    vector center () const override{
        double gx = 0, gy = 0, A = 0;
        size_t n = vertices_count();
        for (size_t i = 0; i < n-1; ++i){
            gx += (vert[i].x + vert[i+1].x) * (vert[i].x * vert[i+1].y - vert[i+1].x * vert[i].y);
            gy += (vert[i].y + vert[i+1].y) * (vert[i].x * vert[i+1].y - vert[i+1].x * vert[i].y);
            A += (vert[i].x * vert[i+1].y - vert[i+1].x * vert[i].y);
        }
        gx += (vert[n-1].x + vert[0].x) * (vert[n-1].x * vert[0].y - vert[0].x * vert[n-1].y);
        gy += (vert[n-1].y + vert[0].y) * (vert[n-1].x * vert[0].y - vert[0].x * vert[n-1].y);
        A += (vert[n-1].x * vert[0].y - vert[0].x * vert[n-1].y);
        A /= 2;
        gx /= 6 * A;
        gy /= 6 * A;
        auto res = vector(gx, gy);
        return res;
    }

    ~polygon() = default;

    double perimeter()const override{
        size_t n = vertices_count();
        double res = 0;
        for(int i = 0; i < n-1; ++i){
            res += dist(vert[i], vert[i+1]);
        }
        res += dist(vert[n-1], vert[0]);
        return res;
    }

    double area()const override{
        size_t n = vertices_count();
        double area = 0;
        for (int i = 0; i < n-1; ++i){
            area += cross_product(vert[i], vert[i+1]);
        }
        area += cross_product(vert[n-1], vert[0]);
        return std::abs(area/2);
    }

    bool operator ==(const polygon &other)const{
        size_t n1 = vertices_count(), n2 = other.vertices_count();
        if(n1 != n2) return false;
        bool res = false;
        for (size_t i = 0; i < n2; ++i){
            if(vert[0] == other.vert[i]){
                res = true;
                size_t idx = i;
                for (size_t j = 1; j < n1; ++j){
                    if(vert[j] != other.vert[(j + idx)%n1]){
                        res = false;
                        break;
                    }
                }
            }
            if (res) break;
        }
        return res;
    }

    bool operator != (const polygon &other)const{
        return !(this->operator==(other));
    }

    void scale (double coefficient)override{
        size_t n = vertices_count();
        vector s = center();
        for (size_t i = 0; i < n; ++i){
            auto tmp = vector(vert[i].x - s.x, vert[i].y - s.y);
            vert[i] = s + coefficient * tmp;
        }
        sort();
    }

    void rotate(double angle)override{
        vector cent = center();
        size_t n = vertices_count();
        for(size_t i = 0; i < n; ++i){
            double x_t = cent.x + (vert[i].x - cent.x) * std::cos(angle) - (vert[i].y - cent.y) * std::sin(angle);
            double y_t = cent.y + (vert[i].x - cent.x) * std::sin(angle) + (vert[i].y - cent.y) * std::cos(angle);
            vert[i] = vector(x_t, y_t);
        }
    }

    void translate(vector transform)override{
        size_t n = vertices_count();
        for(size_t i = 0; i < n; ++i){
            vert[i] += transform;
        }
    }

    bool congruent_to(const polygon &other)const{
        size_t n1 = vertices_count(), n2 = other.vertices_count();
        const double eps = 1e-6;
        bool res = false, res1 = false;
        if(n1 != n2) return false;
        else{
            std::vector<double>l1;
            std::vector<double>l2;
            vector c1 = center();
            vector c2 = other.center();
            for(size_t i = 0; i < n1; ++i){
                l1.push_back((vert[i] - c1).length());
                l2.push_back((other.vert[i] - c2).length());
            }

            for (size_t i = 0; i < n2; ++i){
                if(std::abs(l1[0] - l2[i]) < eps){
                    res = true;
                    size_t idx = i;
                    for (size_t j = 1; j < n1; ++j){
                        if(std::abs(l1[j] - l2[(j + idx)%n1]) > eps){
                            res = false;
                            break;
                        }
                    }
                }
                if (res) break;
            }

            std::reverse(l2.begin(), l2.end());
            for (size_t i = 0; i < n2; ++i){
                if(std::abs(l1[0] - l2[i]) < eps){
                    res1 = true;
                    size_t idx = i;
                    for (size_t j = 1; j < n1; ++j){
                        if(std::abs(l1[j] - l2[(j + idx)%n1]) > eps){
                            res1 = false;
                            break;
                        }
                    }
                }
                if (res1) break;
            }
        }
        return res || res1;
    }

};

//Rectangle:
class rectangle : public polygon{
    vector cen;
    double hgt, wdt;
public:
    rectangle(const vector &c, const double &h, const double &w) :
            polygon({c + vector(-h/2, w/2), c + vector(h/2, w/2), c + vector(h/2, -w/2), c + vector(-h/2, -w/2) }){
        cen = c;
        hgt = h;
        wdt = w;
    }

    vector center()const{
        return cen;
    }

    void scale(double coefficient)override{
        polygon::scale(coefficient);
        hgt *= std::abs(coefficient);
        wdt *= std::abs(coefficient);
    }

    double height()const{
        return hgt;
    }

    double width()const{
        return wdt;
    }

    ~rectangle() = default;

};

//Square:
class square : public rectangle{
    vector cen;
    double l;
public:
    square(const vector &c, const double &len): rectangle(c, len, len){
        cen = c;
        l = len;
    }

    double side()const{
        return l;
    }

    void scale(double coefficient)override{
        rectangle::scale(coefficient);
        l *= std::abs(coefficient);
    }

    circle circumscribed_circle()const{
        auto c = circle(rectangle::center(), side() * std::sqrt(2) * 0.5);
        return c;
    }

    circle inscribed_circle()const{
        auto c = circle(rectangle::center(), side() *  0.5);
        return c;
    }

    ~square() = default;
};

//Triangle:
class triangle : public polygon{
public:
    triangle(const vector &v1, const vector &v2, const vector &v3) : polygon({v1, v2, v3}){};

    circle circumscribed_circle()const{
        double ar = polygon::area();
        auto vec = polygon::get_vertices();
        double rad = (dist(vec[0], vec[1]) * dist(vec[1], vec[2]) * dist(vec[2], vec[0])) / (4 * ar);
        double x0=((vec[0].x*vec[0].x+vec[0].y*vec[0].y)*(vec[1].y-vec[2].y)-vec[0].y*(vec[1].x*vec[1].x+vec[1].y*vec[1].y-vec[2].x*vec[2].x-vec[2].y*vec[2].y)+vec[2].y*(vec[1].x*vec[1].x+vec[1].y*vec[1].y)-vec[1].y*(vec[2].x*vec[2].x+vec[2].y*vec[2].y))/(4*ar);
        double y0 = ((vec[0].x - vec[1].x)*(vec[2].x * vec[2].x + vec[2].y * vec[2].y) +
                     (vec[1].x - vec[2].x)*(vec[0].x * vec[0].x + vec[0].y * vec[0].y) +
                     (vec[2].x - vec[0].x)*(vec[1].x * vec[1].x + vec[1].y * vec[1].y)) /
                    (2 * ((vec[0].x - vec[1].x) * (vec[2].y - vec[0].y) - (vec[0].y - vec[1].y) * (vec[2].x - vec[0].x)));
        auto c = circle(vector(x0, y0), rad);
        return c;
    }

    circle inscribed_circle()const{
        double s = polygon::area();
        auto vec = polygon::get_vertices();
        double a = dist(vec[0], vec[1]);
        double b = dist(vec[1], vec[2]);
        double c = dist(vec[2], vec[0]);
        double P = a + b + c;
        double rad = (2 * s) / P;
        double x0 = (b*vec[0].x + c*vec[1].x + a*vec[2].x)/P;
        double y0 = (b*vec[0].y + c*vec[1].y + a*vec[2].y)/P;
        auto q = circle(vector(x0, y0), rad);
        return q;
    }

    ~triangle() = default;

};
