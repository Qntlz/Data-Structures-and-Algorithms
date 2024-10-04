    #include <stdio.h>
    #include <stdlib.h>
    #include <stdbool.h>

    // SETS UID (Computer Word Implementation)
    // Time Complexity: O(1)

    typedef unsigned int BitVector;

    void initBitVector(BitVector*);
    void insert(BitVector*,int);
    void delete(BitVector*,int);
    bool isMember(BitVector,int);
    BitVector getUnion(BitVector,BitVector);
    BitVector getIntersection(BitVector,BitVector);
    BitVector getDifference(BitVector,BitVector);
    int count(BitVector);


    int main(){

        BitVector S1,S2,S3,S4,S5,S6;

        // Initialize Set
        initBitVector(&S1);
        initBitVector(&S2);
        initBitVector(&S3);
        initBitVector(&S4);
        initBitVector(&S5);
        initBitVector(&S6);

        // Insert Members

        //Set 1
        insert(&S1,1);
        insert(&S1,2);
        insert(&S1,3);
        insert(&S1,4);
        insert(&S1,5);

        //Set 2
        insert(&S2,1);
        insert(&S2,2);
        insert(&S2,3);

        //Set 3
        insert(&S3,3);
        insert(&S3,4);
        insert(&S3,5);

        printf("%u\n",S1);            // Output will be 63 
        /*
            Explanation:
            S1 in binary is = 0000011111

            2^0 + 2^1 + .....2^5 = 62
        */

        delete(&S1,2);
        printf("%u\n",S1);            // Output will be 59
            /*
            Explanation:
            S1 in binary Before deleteing 2 is = 0000011111 
            After deletion = 0000011011 

            62 - 2^2 = 58
        */

        // Check if the following element is a member
        (isMember(S1,2)) ? printf("Member\n") : printf("Not Member\n");     // Output will be "Not Member"

        S4 = getUnion(S2,S3);
        S5 = getIntersection(S2,S3);
        S6 = getDifference(S2,S3);


        printf("Union of Set 2 & Set 3: %u\n",S4);  // Output will be 62
        /*
            Explanation:
            Remember, the contents of our Set 1 = {1,2,3,4,5} which it's decimal value is 62

            From the union(Set 4) of Set 2 & Set 3 which each set is a subset of Set 1,
            Set 4 decimal value must also be 62 
        */

       printf("Intersection of Set 2 & Set 3: %u\n",S5);  // Output will be 8
       /*
            Explanation:
            The only common element between Set 2 & Set 3 is 3. Therefore,
            2^3 = 8
       */

        printf("Difference of Set 2 - Set 3: %u\n",S6);   // Output will be 6
        /*
            Explanation:
            S2 - S3
            {1,2,3} - {3,4,5} = {1,2}

            2^1 + 2^2 = 6
        */

       printf("%d",count(S1));

        return 0;
    }

    void initBitVector(BitVector *Set){
        *Set = 0;
    }

    void insert(BitVector *Set,int elem){
        *Set |= (1 << elem);
    }
    void delete(BitVector *Set,int elem){
        *Set &= ~(1 << elem);
    }
    bool isMember(BitVector Set,int elem){
        return (Set & (1 << elem)) != 0;
    }

    BitVector getUnion(BitVector SetA,BitVector SetB){
        return SetA | SetB;
    }

    BitVector getIntersection(BitVector SetA,BitVector SetB){
        return SetA & SetB;
    }

    BitVector getDifference(BitVector SetA,BitVector SetB){
        return (SetA &~ SetB); 
    }

    int count(BitVector S1){
        return __builtin_popcount(S1);
    }

