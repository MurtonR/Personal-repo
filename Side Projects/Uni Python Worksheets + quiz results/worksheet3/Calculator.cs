using Newtonsoft.Json.Linq;
using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using System.Net;
using System.Text;
using System.Threading.Tasks;

namespace COMP110_FactorioCalculator
{
    public static class Calculator
    {
        public static double GetTotalAssemblyTimeForProduct(string product)
        {
            
            if (Recipes.IsRawMaterial(product) == true)  //Checks to see if the item is a raw material or not
            {
                return 0;
            }
            Double Amount = 1;
            Double productTime = Recipes.FindAssemblyTimeForProduct(product); //This makes the variable "productTime" which is equal to the assembly time of the product

            double AssemblyTime(string product2)
            {
                
                Dictionary<string, double> ingredients = Recipes.FindIngredientsForProduct(product2); //Gets the ingredidients of the product in a dictionary with both the name and quantity of each component

                foreach (KeyValuePair<string, double> item in ingredients) //Iterates through each key value pair in the dictionary 


                {
                    if (Recipes.IsRawMaterial(item.Key) == true)  //Checks to see if this component is a raw material and if it true skips this component
                    {
                        continue;
                    }

                  
                    if (Recipes.IsRawMaterial(item.Key) == false) //Checks to see if this component is a raw material and if it false finds the assembly time of this component and the assembly time of any its components
                    {
                        if (item.Value < 1) //If the quantity of the component is less than 1 then it runs this code
                        {
                            Amount = item.Value; //Sets amount to be the quantity, this is used so that the assembly time is accurate if the quantity is less than 1
                            productTime += Recipes.FindAssemblyTimeForProduct(item.Key) * Amount;
                            AssemblyTime(item.Key);
                            Amount = 1;
                        }
                        else
                        {
                            for (int b = 0; b < item.Value; b++) //iterates through the code for the quantity of the component
                            {
                                productTime += Recipes.FindAssemblyTimeForProduct(item.Key) * Amount;
                                AssemblyTime(item.Key);

                            }
                        }
                       
                        continue;
                    }
                    
           
                    











                }
                return productTime;

            }



            return AssemblyTime(product); //Returns total assembly time for the product
           






        }

        public static Dictionary<string, double> GetRawMaterialsForProduct(string product)
        {
            Double amount = 1;
            Dictionary<string, double> rawProduct = new Dictionary<string, double>();
            Dictionary<string, double> newProduct = new Dictionary<string, double>();
            if (Recipes.IsRawMaterial(product) == true) //Checks to see if the item is a raw material, if true then add the product to a dictionary called "newProduct" with a quantity of 1
            {
                newProduct.Add(product, 1);
                return newProduct;

            }
            Dictionary<string, double> RawMaterials(string product1)
            {
              
                Dictionary<string, double> Ingredient = Recipes.FindIngredientsForProduct(product1); //Finds the ingredients for the product and puts the returned value into a dictionary callwd "Ingredient"
                foreach (KeyValuePair<string, double> Pairs in Ingredient) //Iterates through every key value pair in the dictionary "Ingredient"
                {
                    if (Recipes.IsRawMaterial(Pairs.Key) == true) //Checks to see if the component is a raw material, if true then it adds the Pairs.Value * the amount of product being created to the dictionary "newProduct"
                    {
                        if (newProduct.ContainsKey(Pairs.Key))
                        {
                            newProduct[Pairs.Key] += Pairs.Value * amount ;
                            continue;
                        }
                        else
                        {
                            newProduct.Add(Pairs.Key, Pairs.Value * amount);
                            continue;
                        }
                        

                    }
                    if (Recipes.IsRawMaterial(Pairs.Key) == false) //Checks to see if the component is a raw material, if false then it makes amount equal the quantity of product and checks the components of the product by calling this function but with the product as the argument
                    {

                        if (Pairs.Value < 1)
                        {
                            amount = Pairs.Value;
                            RawMaterials(Pairs.Key);
                            amount = 1;
                        }
                        else
                        {
                            for (int b = 0; b < Pairs.Value; b++)
                            {

                                RawMaterials(Pairs.Key);

                            }
                        }
                       
                        continue;
                    }







                }

                return newProduct;

            }

            
            return RawMaterials(product); //Returns the total assembly time for this product
        }
            
          


    }
    }


