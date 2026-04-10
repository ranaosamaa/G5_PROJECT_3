#include <iostream>
#include <string>
//#include <bits/stdc++.h>
using namespace std;

class BigInt {
    string number;    // Stores the number as a string
    bool isNegative;  // True if number is negative

    // Remove unnecessary leading zeros from the number string
    void removeLeadingZeros() {
        // TODO: Implement this function
        int i=0;
        while (i< (int)number.size()-1 && number[i]=='0') i++;
        number=number.substr(i);
        // If no becomes "0", make sure sign is not -ve
        if (number == "0") isNegative = false;
    }

    // Compare absolute values of two BigInts (ignore signs)
    // Returns: 1 if |this| > |other|, 0 if equal, -1 if |this| < |other|
    int compareMagnitude(const BigInt& other) const {
        // TODO: Implement this function
        if (this->number.length() > other.number.length()) {
            return 1;
        }
        else if(this->number.length() < other.number.length())
            return -1;

        for (int i = 0; i < this->number.length(); i++) {
            if (this->number[i] > other.number[i]) {
                return 1;
            }
            else if (this->number[i] < other.number[i]) {
                return -1;
            }
        }
        return 0;
    }

    string subtractStrings(string s1, string s2) {
        string result = "";
        int borrow = 0;

        reverse(s1.begin(), s1.end());
        reverse(s2.begin(), s2.end());

        for (int i = 0; i < s1.size(); i++) {
            int digit1 = s1[i] - '0';
            int digit2 = i < s2.size() ? s2[i] - '0':0;

            digit1 -= borrow;
            if (digit1 < digit2) {
                digit1 += 10;
                borrow = 1;
            }
            else borrow = 0;

            result += (digit1 - digit2) + '0';
        }
        reverse(result.begin(), result.end());
        int i = 0;
        while (i < result.size() - 1 && result[i] == '0') i++;
        return result.substr(i);
    }
    // a helper function to add two strings 
    string addstrings(string s1 , string s2){
        // identfiy a result string
        string result = "";
        int Carry = 0;
        reverse(s1.begin(), s1.end());
        reverse(s2.begin(), s2.end());  
        // looping through the strings
        int i =0;
        int j =0;
        int sum =0;
        int dig1 = 0;
        int dig2 =0;
        while(i<s1.size() || j<s2.size() || Carry!=0 ){
            if (i < s1.size()){
                dig1 = s1[i] -'0';   
            }
            else {
                dig1=0;
            }
            if (j < s2.size()){

                dig2 = s2[j] -'0';
            }
            else {
                dig2=0;
            }
            sum = (dig1+dig2)+Carry; 
            int Rdig = sum %10;
            result +=(Rdig +'0');

            Carry = (sum /10);

            i++;
            j++;
        }     
        reverse(result.begin(), result.end());
        return result;
    }
public:
    // Default constructor - initialize to zero
    BigInt() {
        // TODO: Implement this constructor
        number = "0";
        isNegative = false;
    }

    // Constructor from 64-bit integer
    BigInt(int64_t value) {
        if (value < 0)
            isNegative = true;
        number = abs(value);
        // TODO: Implement this constructor
    }

    // Constructor from string representation
    BigInt(const string& str) {
        // TODO: Implement this constructor
        // chec if the string is starting with - 
        if(str[0] == '-'){
            isNegative = true;
            number = str.substr(1);
        }
        else {
            isNegative = false;
            number = str;
        }
        // call leading zer0 functoin
        removeLeadingZeros();
    }

    // Copy constructor
   BigInt(const BigInt& other) {
    this->number = other.number;
    this->isNegative = other.isNegative;
}

    // Destructor
    ~BigInt() {
        // TODO: Implement if needed
    }

    // Assignment operator
    BigInt& operator=(const BigInt& other) {
        if (this != &other) {
        this->number = other.number;
        this->isNegative = other.isNegative;
    }
        return *this;
    }

    // Unary negation operator (-x)
    BigInt operator-() const {
        BigInt result;
        result.number = this->number;
        result.isNegative = !(this->isNegative);
        return result;
    }

    // Unary plus operator (+x)
    BigInt operator+() const {
        BigInt result;
        result.number = this->number;
        result.isNegative = this->isNegative;
        return result;
    }

    // Addition assignment operator (x += y)
    BigInt& operator+=(const BigInt& other) {
        // TODO: Implement this operator
        if (this->isNegative == other.isNegative) {
            this->number = addstrings(this->number, other.number);
        }
        else {
            int cmp = compareMagnitude(other);

            if (cmp == 0) {
                this->number = "0";
                this->isNegative = false;
            }
            else if (cmp == 1) {
                this->number = subtractStrings(this->number, other.number);
            }
            else {
                this->isNegative = other.isNegative;
                this->number = subtractStrings(other.number, this->number);
            }
        }
        removeLeadingZeros();
        return *this;
    }

    // Subtraction assignment operator (x -= y)
    BigInt& operator-=(const BigInt& other) {
        // TODO: Implement this operator
        return *this;
    }

    // Multiplication assignment operator (x *= y)
    BigInt& operator*=(const BigInt& other) {
        string result = "0";
        for (int i = number.size() - 1; i >= 0; i--) {
            int carry = 0;
            string temp = "";

            for (int k = 0; k < number.size() - 1; k++)
                temp += '0';

            for (int j = other.number.size() - 1; j >= 0; j--) {
                int mul = (number[i] - '0') * (other.number[j] - '0') + carry;
                temp = char(mul % 10 + '0') + temp;
                carry = mul / 10;
            }
            if (carry) temp = char(carry + '0') + temp;
            result = addstrings(result, temp);
        }
        number = result;
        isNegative = (isNegative != other.isNegative);
        removeLeadingZeros();
        return *this;
    }

    // Division assignment operator (x /= y)
    BigInt& operator/=(const BigInt& other) {
        // TODO: Implement this operator
        // Div by 0
        if (other.number=="0") throw runtime_error("Division by zero");
        // If this is 0
        if (number=="0") return *this;

        BigInt divisor=other;
        divisor.isNegative=false;

        BigInt current("0");
        string result="";

        for (char digit:number) {
            // current=current*10 + digit
            current.number+=digit;
            current.removeLeadingZeros();
            int count=0;
            while (current.compareMagnitude(divisor)>=0) {
                current -= divisor;
                count++;
            }
            result += (count+'0');
        }
        number=result;
        removeLeadingZeros();
        // Sign handle
        isNegative= (isNegative!=other.isNegative);
        // If res is 0 -> no -ve
        if (number=="0") {
            isNegative=false;
        }

        return *this;
    }

    // Modulus assignment operator (x %= y)
    BigInt& operator%=(const BigInt& other) {
        if (other.number == "0")
        throw runtime_error("Division by zero");

    if (number == "0")
        return *this;

    bool originalSign = isNegative;

    BigInt divisor = other;
    divisor.isNegative = false;

    BigInt remainder("0");
    remainder.isNegative = false;

    for (char digit : number) {
        remainder.number += digit;
        remainder.removeLeadingZeros();

        while (remainder.compareMagnitude(divisor) >= 0) {
            remainder.number = subtractStrings(remainder.number, divisor.number);
            remainder.removeLeadingZeros();
        }
    }

    number = remainder.number;
    isNegative = (number == "0") ? false : originalSign;

        return *this;
    }

    // Pre-increment operator (++x)
    BigInt& operator++() {
        // TODO: Implement this operator
        *this += BigInt(1);
        return *this;
    }

    // Post-increment operator (x++)
    BigInt operator++(int) {
        BigInt temp;
        *this += BigInt(1);
        return temp;
    }

    // Pre-decrement operator (--x)
    BigInt& operator--() {
        // TODO: Implement this operator
        return *this;
    }

    // Post-decrement operator (x--)
    BigInt operator--(int) {
        BigInt temp;
        *this -= BigInt(1);
        return temp;
    }

    // Convert BigInt to string representation
    string toString() const {
        // TODO: Implement this function
        if (number == "0") return "0"; // zero has no sign
        return (isNegative ? "-" : "") + number;
    }

    // Output stream operator (for printing)
    friend ostream& operator<<(ostream& os, const BigInt& num) {
        os << num.toString();
        return os;
    }

    // Input stream operator (for reading from input)
    friend istream& operator>>(istream& is, BigInt& num) {
        string s;
        is >> s;
        num = BigInt(s);
        return is;
    }

    // Friend declarations for comparison operators
    friend bool operator==(const BigInt& lhs, const BigInt& rhs);
    friend bool operator<(const BigInt& lhs, const BigInt& rhs);
};

// Binary addition operator (x + y)
BigInt operator+(BigInt lhs, const BigInt& rhs) {
    BigInt result;
    // TODO: Implement this operator
    return result;
}

// Binary subtraction operator (x - y)
BigInt operator-(BigInt lhs, const BigInt& rhs) {
    BigInt result;
    result = lhs;
    result -= rhs;
    return result;
}

// Binary multiplication operator (x * y)
BigInt operator*(BigInt lhs, const BigInt& rhs) {
    BigInt result;
    // TODO: Implement this operator
    result=lhs;   // copy lft oper
    result*=rhs;         // use mult assig
    return result;
}

// Binary division operator (x / y)
BigInt operator/(BigInt lhs, const BigInt& rhs) {
    BigInt result;
    // TODO: Implement this operator
    return result;
}

// Binary modulus operator (x % y)
BigInt operator%(BigInt lhs, const BigInt& rhs) {
    BigInt result;
    result = lhs;
    result %= rhs;
    return result;
}

// Equality comparison operator (x == y)
bool operator==(const BigInt& lhs, const BigInt& rhs) {
    // TODO: Implement this operator
    if (lhs.number == rhs.number && lhs.number == "0")
        return true;
    if (lhs.isNegative != rhs.isNegative)
        return false;
    return lhs.number == rhs.number;
}

// Inequality comparison operator (x != y)
bool operator!=(const BigInt& lhs, const BigInt& rhs) {
    // TODO: Implement this operator
    return !(lhs == rhs);
}

// Less-than comparison operator (x < y)
bool operator<(const BigInt& lhs, const BigInt& rhs) {
    if (lhs.isNegative != rhs.isNegative)
        return lhs.isNegative;

    // same sign
    int cmp = lhs.compareMagnitude(rhs);

    if (!lhs.isNegative) {
        // both positive
        return cmp == -1;
    } else {
        // both negative (reverse)
        return cmp == 1;
    }
    return false;
}

// Less-than-or-equal comparison operator (x <= y)
bool operator<=(const BigInt& lhs, const BigInt& rhs) {
    
    return (lhs<rhs)||(lhs==rhs);
}

// Greater-than comparison operator (x > y)
bool operator>(const BigInt& lhs, const BigInt& rhs) {
    // TODO: Implement this operator
    return (rhs < lhs);
}

// Greater-than-or-equal comparison operator (x >= y)
bool operator>=(const BigInt& lhs, const BigInt& rhs) {
    // TODO: Implement this operator
    return !(lhs < rhs);
}

int main() {
    cout << "=== BigInt Class Test Program ===" << endl << endl;
    cout << "NOTE: All functions are currently empty." << endl;
    cout << "Your task is to implement ALL the functions above." << endl;
    cout << "The tests below will work once you implement them correctly." << endl << endl;

    /*
    // Test 1: Constructors and basic output
    cout << "1. Constructors and output:" << endl;
    BigInt a(12345);              // Should create BigInt from integer
    BigInt b("-67890");           // Should create BigInt from string
    BigInt c("0");                // Should handle zero correctly
    BigInt d = a;                 // Should use copy constructor
    cout << "a (from int): " << a << endl;        // Should print "12345"
    cout << "b (from string): " << b << endl;     // Should print "-67890"
    cout << "c (zero): " << c << endl;            // Should print "0"
    cout << "d (copy of a): " << d << endl << endl; // Should print "12345"

    // Test 2: Arithmetic operations
    cout << "2. Arithmetic operations:" << endl;
    cout << "a + b = " << a + b << endl;          // Should calculate 12345 + (-67890)
    cout << "a - b = " << a - b << endl;          // Should calculate 12345 - (-67890)
    cout << "a * b = " << a * b << endl;          // Should calculate 12345 * (-67890)
    cout << "b / a = " << b / a << endl;          // Should calculate (-67890) / 12345
    cout << "a % 100 = " << a % BigInt(100) << endl << endl; // Should calculate 12345 % 100

    // Test 3: Relational operators
    cout << "3. Relational operators:" << endl;
    cout << "a == d: " << (a == d) << endl;       // Should be true (12345 == 12345)
    cout << "a != b: " << (a != b) << endl;       // Should be true (12345 != -67890)
    cout << "a < b: " << (a < b) << endl;         // Should be false (12345 < -67890)
    cout << "a > b: " << (a > b) << endl;         // Should be true (12345 > -67890)
    cout << "c == 0: " << (c == BigInt(0)) << endl << endl; // Should be true (0 == 0)

    // Test 4: Unary operators and increments
    cout << "4. Unary operators and increments:" << endl;
    cout << "-a: " << -a << endl;                 // Should print "-12345"
    cout << "++a: " << ++a << endl;               // Should increment and print "12346"
    cout << "a--: " << a-- << endl;               // Should print "12346" then decrement
    cout << "a after decrement: " << a << endl << endl; // Should print "12345"

    // Test 5: Large number operations
    cout << "5. Large number operations:" << endl;
    BigInt num1("12345678901234567890");
    BigInt num2("98765432109876543210");
    cout << "Very large addition: " << num1 + num2 << endl;
    cout << "Very large multiplication: " << num1 * num2 << endl << endl;

    // Test 6: Edge cases and error handling
    cout << "6. Edge cases:" << endl;
    BigInt zero(0);
    BigInt one(1);
    try {
        BigInt result = one / zero;               // Should throw division by zero error
        cout << "Division by zero succeeded (unexpected)" << endl;
    } catch (const runtime_error& e) {
        cout << "Division by zero correctly threw error: " << e.what() << endl;
    }
    cout << "Multiplication by zero: " << one * zero << endl;        // Should be "0"
    cout << "Negative multiplication: " << BigInt(-5) * BigInt(3) << endl;  // Should be "-15"
    cout << "Negative division: " << BigInt(-10) / BigInt(3) << endl;       // Should be "-3"
    cout << "Negative modulus: " << BigInt(-10) % BigInt(3) << endl;        // Should be "-1"
    */

    return 0;
}