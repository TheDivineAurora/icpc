int gcd(int a, int b, int& x, int& y) {
    if (b == 0) {
        x = 1, y = 0;
        return a;
    }
    int x1, y1;
    int g = gcd(b, a % b, x1, y1);
    x = y1;
    y = x1 - y1 * (a / b);
    return g;
};

bool sol(int a, int b, int c, int& x, int& y) {
    int x1, y1;
    int g = gcd(abs(a), abs(b), x1, y1);
    if (c % g) {
        return false;
    }
    // ax1 + by1 = g
    if (a < 0) x1 *= -1;
    if (b < 0) y1 *= -1;
    // ax1 * c/g + by1 * c/g = c
    x1 *= (c / g);
    y1 *= (c / g);
    x = x1, y = y1;
    return true;
}
