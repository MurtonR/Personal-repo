using System.ComponentModel.Design;
using System.Diagnostics;
using System.Diagnostics.Metrics;
using System.Globalization;
using System.Net.Http.Headers;
using System.Runtime.CompilerServices;
using System.Runtime.Intrinsics;
using System.Text;

namespace comp101_worksheet2
{

    public class Program
    {

        public static void Main(string[] args)
        {
            
        }
        
        /* CONVERSION LOGIC BELOW */
        
        /// <summary>
        /// Convert one 'ascii' character to hexadecimal 
        /// </summary>
        /// <param name="myValue">The value to convert</param>
        /// <returns>A value between 0-16 if valid, else -1</returns>
        public static int HexDigit(char myValue)
        {
            if ('0' <= myValue && myValue <= '9')
            {
                return myValue - '0';
            } else if ('A' <= myValue && myValue <= 'F')
            {
                return (myValue - 'A') + 10;
            }

            return -1;
        }

        /// <summary>
        /// Convert a provided integer to hexadecimal.
        /// </summary>
        /// 
        /// <param name="value">the integer to convert</param>
        /// <returns>The hexadecimal value, or "ERROR" if invalid</returns>
        
        public static string ConvertToHex(int value)
        {
        
            if (0 <= value && value <= 255)
            {

                value = Convert.ToInt32(value);
                string hexValue = value.ToString("X");
                hexValue = "0x" + hexValue;
                return hexValue;

            }
            else
            {
                return "ERROR";
            }
           
        }


        /// <summary>
        /// Convert a provided hexadecimal string to an integer.
        /// </summary>
        /// 
        /// <param name="hexString">the hexadecimal value</param>
        /// <returns>The corresponding (base 10) integer, or -1 on error</returns>
        public static int ConvertToInt(string hexString)
        {
            if (hexString.StartsWith("0x"))
            {
                try
                {
                    int value = Convert.ToInt32(hexString, 16);
                    return value;
                }
                catch (System.FormatException)
                {
                    return -1;
                }

            }
            else
            {
                return -1;
            }
        }
        
        /// <summary>
        /// Convert a 'middle endian' hex value back to it's integer version.
        /// </summary>
        /// 
        /// <param name="hexString">the 'middle endian' hexadecimal value</param>
        /// <returns>The corresponding (base 10) integer, or -1 on error</returns>
        public static int ChallengeMiddleEndianHex(string hexString)
        {
            if (hexString.Length == 6)
                try
                {
                    var hexCon = new StringBuilder(hexString);
                    var startIndex = 2; 
                    var length = 2; 
                    string firstEndian = hexCon.ToString(startIndex, length);
                    var start = 4;
                    var length1 = 2;
                    string lastEndian = hexCon.ToString(start, length1);
                    
                    hexString = "0x"+lastEndian+firstEndian;

                   
                    int value = Convert.ToInt32(hexString, 16);
                return value;

                   

                }
                catch (System.FormatException)
                {
                    return -1;
                }
            else
            {

                return -1;
            }
            
          

        }
        
        /* VECTOR LOGIC BELOW */

        public static float[] addVectors(float[] vec1, float[] vec2)
        {
            Debug.Assert(vec1.Length == vec2.Length); // allowed to assume both arrays are the same size
            return new float[2] { vec1[0] + vec2[0] , vec1[1] + vec2[1] };
        }
        
        public static float[] subVectors(float[] vec1, float[] vec2)
        {
            Debug.Assert(vec1.Length == vec2.Length); // allowed to assume both arrays are the same size
            return new float[2] { vec1[0] - vec2[0], vec1[1] - vec2[1] };
        }
        
        public static float lengthVector(float[] vec)
        {
            
            Debug.Assert(vec.Length == 2); // allowed to assume 2D vector
            float vec1 = (vec[0] * vec[0]);
            float vec2 = (vec[1] * vec[1]);
            float venlenght = (vec1 + vec2);
            // HINT: MathF.Sqrt does square root for floats...
            venlenght = MathF.Sqrt(venlenght);
            return venlenght;
        }
        
        public static float vectorDistance(float[] vec1, float[] vec2)
        {
            Debug.Assert(vec1.Length == vec2.Length); // allowed to assume both arrays are the same size
            return 0.0F;
        }
        
    }
    
}

