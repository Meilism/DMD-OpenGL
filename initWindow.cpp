#include "mex.hpp"
#include "mexAdapter.hpp"

class MexFunction: public matlab::mex::Function {
    public:
        void operator()(matlab::mex::ArgumentList outputs, matlab::mex::ArgumentList inputs){
            
        }
        void initWindow(matlab::data::TypedArray<double>& inMatrix){
        
        }
        void checkArguments(matlab::mex::ArgumentList outputs, matlab::mex::ArgumentList inputs){
            
        }
};