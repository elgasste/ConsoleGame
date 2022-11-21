using System;
using System.IO;
using System.Text.RegularExpressions;

namespace ConsoleGameSolutionSetup
{
   class Program
   {
      const string ConsoleGameName = "ConsoleGame";

      static string GetNewSolutionName()
      {
         Regex alphaRegEx = new Regex( "^[a-zA-Z ]+$" );

         while ( true )
         {
            Console.Write( "My sweet game's solution name is: " );
            var newSolutionName = Console.ReadLine();

            if ( string.IsNullOrEmpty( newSolutionName ) )
            {
               Console.WriteLine( "\nYour game is called \"\"? Even if that was intentional, you can't have a blank solution name, sorry!\n" );
            }
            else if ( newSolutionName.Contains( ' ' ) )
            {
               Console.WriteLine( "\nWhat did I say about spaces? No spaces! Let's try this again.\n" );
            }
            else if ( newSolutionName.Length >= 100 )
            {
               Console.WriteLine( "\nI said \"try\" to keep it under 100 characters, but what I really meant was you HAVE to. Can't you make it shorter?\n" );
            }
            else if ( !alphaRegEx.IsMatch( newSolutionName ) )
            {
               Console.WriteLine( "\nMy spidey sense tells me something in there is not a letter, let's try that again.\n" );
            }
            else
            {
               return newSolutionName;
            }
         }
      }

      static void RenameAllFiles( string newSolutionName )
      {
         var currentDirectory = Directory.GetCurrentDirectory();

         // solution directory
         var origSolutionFilePath = Path.Combine( currentDirectory, $"{ConsoleGameName}.sln" );
         if ( !File.Exists( origSolutionFilePath ) )
         {
            Console.WriteLine( $"Hmm, I couldn't find the solution file \"{ConsoleGameName}.sln\", are you sure this is the right folder?" );
            Console.WriteLine( "Make sure this utility is in the root folder of the repo and try again!" );
            return;
         }

         // solution file
         Console.Write( "Renaming solution file..." );
         var newSolutionFilePath = Path.Combine( currentDirectory, $"{newSolutionName}.sln" );
         try
         {
            File.Move( origSolutionFilePath, newSolutionFilePath );
            Console.Write( "done!\n" );
         }
         catch
         {
            Console.WriteLine( "gah, Something went wrong!\n\nDoes the new solution already exist? Is it aliens? I don't know!" );
            return;
         }

         Console.Write( "Rewriting solution file..." );
         var solutionText = File.ReadAllText( newSolutionFilePath );
         solutionText = solutionText.Replace( ConsoleGameName, newSolutionName );
         File.WriteAllText( newSolutionFilePath, solutionText );
         Console.Write( "done!\n" );

         // project directory
         Console.Write( "Renaming project directory..." );
         var origProjectDirectory = Path.Combine( currentDirectory, ConsoleGameName );
         if ( !Directory.Exists( origProjectDirectory ) )
         {
            Console.WriteLine( "something's wrong here, the project directory doesn't exist... WHAT DID YOU DO?" );
            return;
         }
         var newProjectDirectory = Path.Combine( currentDirectory, newSolutionName );
         Directory.Move( origProjectDirectory, newProjectDirectory );
         Console.WriteLine( "done!" );

         // project file
         Console.Write( "Renaming project file..." );
         var origProjectFilePath = Path.Combine( newProjectDirectory, $"{ConsoleGameName}.vcxproj" );
         var newProjectFilePath = Path.Combine( newProjectDirectory, $"{newSolutionName}.vcxproj" );
         try
         {
            File.Move( origProjectFilePath, newProjectFilePath );
            Console.Write( "done!\n" );
         }
         catch
         {
            Console.WriteLine( "gah, Something went wrong!\n\nWhat's going on here? Are you sure you're using a clean version of the original repo?" );
            return;
         }

         Console.Write( "Rewriting project file..." );
         var projectText = File.ReadAllText( newProjectFilePath );
         projectText = projectText.Replace( ConsoleGameName, newSolutionName );
         File.WriteAllText( newProjectFilePath, projectText );
         Console.WriteLine( "done!" );

         // project filters file
         Console.Write( "Renaming project filters file..." );
         var origProjectFiltersFilePath = Path.Combine( newProjectDirectory, $"{ConsoleGameName}.vcxproj.filters" );
         var newProjectFiltersFilePath = Path.Combine( newProjectDirectory, $"{newSolutionName}.vcxproj.filters" );
         try
         {
            File.Move( origProjectFiltersFilePath, newProjectFiltersFilePath );
            Console.Write( "done!\n" );
         }
         catch
         {
            Console.WriteLine( "gah, Something went wrong!\n\nWhat's going on here? Are you sure you're using a clean version of the original repo?" );
            return;
         }

         Console.Write( "Rewriting project Filters file..." );
         var projectFiltersText = File.ReadAllText( newProjectFiltersFilePath );
         projectFiltersText = projectFiltersText.Replace( ConsoleGameName, newSolutionName );
         File.WriteAllText( newProjectFiltersFilePath, projectFiltersText );
         Console.WriteLine( "done!" );

         // header files
         Console.Write( "Rewriting main project header files..." );
         foreach( var file in Directory.GetFiles( newProjectDirectory, "*.h" ) )
         {
            var fileText = File.ReadAllText( file );
            fileText = fileText.Replace( $"namespace {ConsoleGameName}", $"namespace {newSolutionName}" );
            fileText = fileText.Replace( $"{ConsoleGameName}::", $"{newSolutionName}::" );
            File.WriteAllText( file, fileText );
         }
         Console.WriteLine( "done!" );

         // source files
         Console.Write( "Rewriting main project source files..." );
         foreach ( var file in Directory.GetFiles( newProjectDirectory, "*.cpp" ) )
         {
            var fileText = File.ReadAllText( file );
            fileText = fileText.Replace( $"namespace {ConsoleGameName}", $"namespace {newSolutionName}" );
            fileText = fileText.Replace( $"{ConsoleGameName}::", $"{newSolutionName}::" );
            File.WriteAllText( file, fileText );
         }
         Console.WriteLine( "done!" );

         // tests project directory
         Console.Write( "Renaming test project directory..." );
         var origTestProjectDirectory = Path.Combine( currentDirectory, $"{ConsoleGameName}Tests" );
         if ( !Directory.Exists( origTestProjectDirectory ) )
         {
            Console.WriteLine( "uh oh, the test project directory doesn't exist... WHY DO YOU HATE TESTS?" );
            return;
         }
         var newTestProjectDirectory = Path.Combine( currentDirectory, $"{newSolutionName}Tests" );
         Directory.Move( origTestProjectDirectory, newTestProjectDirectory );
         Console.WriteLine( "done!" );

         // tests project file
         Console.Write( "Renaming test project file..." );
         var origTestProjectFilePath = Path.Combine( newTestProjectDirectory, $"{ConsoleGameName}Tests.vcxproj" );
         var newTestProjectFilePath = Path.Combine( newTestProjectDirectory, $"{newSolutionName}Tests.vcxproj" );
         try
         {
            File.Move( origTestProjectFilePath, newTestProjectFilePath );
            Console.Write( "done!" );
         }
         catch
         {
            Console.WriteLine( "gah, Something went wrong!\n\nWhat's going on here? Are you sure you're using a clean version of the original repo?" );
            return;
         }

         Console.Write( "Rewriting test project file..." );
         var testProjectText = File.ReadAllText( newTestProjectFilePath );
         testProjectText = testProjectText.Replace( ConsoleGameName, newSolutionName );
         File.WriteAllText( newTestProjectFilePath, testProjectText );
         Console.WriteLine( "done!" );

         // tests project filters file
         Console.Write( "Renaming test project filters file..." );
         var origTestProjectFiltersFilePath = Path.Combine( newTestProjectDirectory, $"{ConsoleGameName}Tests.vcxproj.filters" );
         var newTestProjectFiltersFilePath = Path.Combine( newTestProjectDirectory, $"{newSolutionName}Tests.vcxproj.filters" );
         try
         {
            File.Move( origTestProjectFiltersFilePath, newTestProjectFiltersFilePath );
            Console.Write( "done!\n" );
         }
         catch
         {
            Console.WriteLine( "gah, Something went wrong!\n\nWhat's going on here? Are you sure you're using a clean version of the original repo?" );
            return;
         }

         Console.Write( "Rewriting test project filters file..." );
         var testProjectFiltersText = File.ReadAllText( newTestProjectFiltersFilePath );
         testProjectFiltersText = testProjectFiltersText.Replace( ConsoleGameName, newSolutionName );
         File.WriteAllText( newTestProjectFiltersFilePath, testProjectFiltersText );
         Console.WriteLine( "done!\n" );

         // test header files
         Console.Write( "Rewriting test project header files..." );
         foreach ( var file in Directory.GetFiles( newTestProjectDirectory, "*.h" ) )
         {
            var fileText = File.ReadAllText( file );
            fileText = fileText.Replace( $"namespace {ConsoleGameName}", $"namespace {newSolutionName}" );
            fileText = fileText.Replace( $"{ConsoleGameName}::", $"{newSolutionName}::" );
            fileText = fileText.Replace( $"<{ConsoleGameName}/", $"<{newSolutionName}/" );
            File.WriteAllText( file, fileText );
         }
         Console.WriteLine( "done!" );

         // test source files
         Console.Write( "Rewriting test project source files..." );
         foreach ( var file in Directory.GetFiles( newTestProjectDirectory, "*.cpp" ) )
         {
            var fileText = File.ReadAllText( file );
            fileText = fileText.Replace( $"namespace {ConsoleGameName}", $"namespace {newSolutionName}" );
            fileText = fileText.Replace( $"{ConsoleGameName}::", $"{newSolutionName}::" );
            fileText = fileText.Replace( $"<{ConsoleGameName}/", $"<{newSolutionName}/" );
            File.WriteAllText( file, fileText );
         }
         Console.WriteLine( "done!" );

         // entry point
         Console.Write( "Renaming entry point..." );
         var origEntryPointFilePath = Path.Combine( newProjectDirectory, $"{ConsoleGameName}.cpp" );
         var newEntryPointFilePath = Path.Combine( newProjectDirectory, $"{newSolutionName}.cpp" );
         try
         {
            File.Move( origEntryPointFilePath, newEntryPointFilePath );
            Console.Write( "done!\n" );
         }
         catch
         {
            Console.WriteLine( "noooo!!\n\nThis is all just SO BAD! Are you using a clean version of the original repo?!" );
            return;
         }

         Console.WriteLine( $"\nCongratulations, you're the lead developer of {newSolutionName} now!" );
         Console.WriteLine( "It's quite the honor, welcome to the club!\n" );
      }

      static void Main( string[] args )
      {
         Console.WriteLine( $"Hello there! You must be here because you want EXCITEMENT, but \"{ConsoleGameName}\" sounds dumb and boring, and I get it." );
         Console.WriteLine( $"Before we start, make sure this utility is in the root folder of the {ConsoleGameName} repo, otherwise it won't work." );
         Console.WriteLine( "On that note, what do you want your game's solution to be called?\n" );
         Console.WriteLine( "(just a reminder: no spaces, try to keep it under 100 characters, and only letters are allowed!)\n" );

         var newSolutionName = string.Empty;

         var keepName = false;
         while ( !keepName )
         {
            newSolutionName = GetNewSolutionName();

            Console.WriteLine( $"\nSo before moving forward, you're sure you want to go with \"{newSolutionName}\"?" );
            Console.WriteLine( "I'm about to rename a TON of things, so make sure you're sure!\n" );

            while ( true )
            {
               Console.Write( "(y/n): " );
               var decision = Console.ReadLine().ToLower();

               if ( decision == "y" )
               {
                  keepName = true;
                  break;
               }
               else if ( decision == "n" )
               {
                  Console.WriteLine( "\nFair enough, what name do you REALLY want then?\n" );
                  break;
               }
               else
               {
                  Console.WriteLine( "\nYou've gotta tell me yes or no with a \"y\" or an \"n\".\n" );
               }
            }
         }

         Console.WriteLine( "\nExcellent, let's get to it!\n" );
         RenameAllFiles( newSolutionName );

         Console.WriteLine( "(press any key to get out of here)" );
         Console.ReadKey();
      }
   }
}
