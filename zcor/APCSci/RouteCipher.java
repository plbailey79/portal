public class RouteCipher
{
    /** A two-dimensional array of single-character strings, instantiated in the constructor */
    private String[][] letterBlock;

    /** The number of rows of letterBlock, set by the constructor */
    private int numRows;

    /** The number of columns of letterBlock, set by the constructor */
    private int numCols;

    /** Places a string into letterBlock in row-major order.
     * @param str the string to be processed
     * Postcondition:
     * if str.length() < numRows * numCols, "A" is placed in each unfilled cell
     * if str.length() > numRows * numCols, trailing characters are ignored
     */
    
    public RouteCipher(int rows, int cols)
    {
        numRows = rows;
        numCols = cols;
        letterBlock = new String[numRows][numCols];
    }
    
    private void fillBlock(String str)
    { 
    }

    /** Extracts encrypted string from letterBlock in column-major order.
     * Precondition: letterBlock has been filled
     * @return the encrypted string from letterBlock
     */

    private String encryptBlock()
    { 
        String s = "";
        return s;
    }

    /** Encrypts a message.
     * @param message the string to be encrypted
     * @return the encrypted message;
     * if message is the empty string, returns the empty string
     */

    public String encryptMessage(String message)
    { 
        String s = "";
        return s;
    }

}

