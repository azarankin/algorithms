#include <iostream>
#include <stack>
#include <sstream>
#include <string>

// ✅ פונקציה לחישוב ביטוי חשבוני עם סוגריים ע"י שתי מחסניות
double evaluateExpression(const std::string& expression) {
    std::stack<std::string> ops;   // מחסנית אופרטורים
    std::stack<double> vals;       // מחסנית ערכים

    std::istringstream iss(expression);
    std::string token;

    while (iss >> token) 
    {
        if (token == "(") 
        {
            // מתעלמים
        }
        else if (token == "+" || token == "-" || token == "*" || token == "/") 
        {
            ops.push(token);
        }
        else if (token == ")") 
        {
            // שולפים אופרטור וערך אחד
            std::string op = ops.top();
            ops.pop();
            double v1 = vals.top();
            vals.pop();
            double v2 = vals.top();
            vals.pop();

            double res = 0;
            // מפעילים את האופרטור על שני הערכים האחרונים
            if (op == "+") res = v2 + v1;
            else if (op == "-") res = v2 - v1;
            else if (op == "*") res = v2 * v1;
            else if (op == "/") res = v2 / v1;

            
            vals.push(res);
        }
        else 
        {
            // המרה ממחרוזת למספר ודחיפה למחסנית הערכים
            vals.push(std::stod(token));
        }
    }

    // ערך יחיד נשאר במחסנית הערכים — התוצאה הסופית
    return vals.top();
}

int main() 
{
    std::string expr = "( 1 + ( ( 2 + 3 ) * ( 4 * 5 ) ) )";
    double result = evaluateExpression(expr);
    std::cout << "Expression: " << expr << "\n";
    std::cout << "Result: " << result << "\n";
    return 0;
}
