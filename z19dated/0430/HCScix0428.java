package customerproject;

public class Customer implements Comparable<Customer>
{
    private String name;
    private int idNum;
    
    public Customer(String name, int idNum)
    {
        this.name = name;
        this.idNum = idNum;
    }
    
    public String getName() { return name; }
    public int getId() { return idNum; }
    
    public String toString()
    {
        return name + ":" + idNum;
    }
    
    public int compareTo(Customer that)
    {
        return compareCustomer(that);
    }
    
    public int compareCustomer(Customer other)
    {
        int v = name.compareTo(other.name);
        if (v == 0)
        {
            v = idNum - other.idNum;
        }
        return v;
    }
    
    public static void prefixMerge(
        Customer[] list1,
        Customer[] list2,
        Customer[] result)
    {
        int i = 0;
        int j = 0;
        int k = 0;
        
        while (k < result.length)
        {
            int v = list1[i].compareCustomer(list2[j]);
            if (v < 0)
            {
                result[k++] = list1[i++];
            }
            if (v > 0)
            {
                result[k++] = list2[j++];
            }
            if (v == 0)
            {
                result[k++] = list1[i++];
                j++;
            }
        } 
    }
}
