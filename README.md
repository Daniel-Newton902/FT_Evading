# FT_Evading
A small project where you evade being hit by various colliders, use the left shift key to perform a dash.
## Overview
In this project you will look at using collision layers to allow the player to temporaly avoid attacks.

## Where to find the relevant scripts

Since we are using a varient project some of the script for the character are in the platformer folder, the scripts we create will still be in the public folder in the source directory.
![Location of the scripts](Hints/Scripts.png)

The primary Actors are in **Content->Varient_Platforming->Blueprints**
-  **BP_Platforming character**, is unreals pre-built platformer with a double jump and dash ability, which we will modify. 
- **My Auto Cannon**, this is the cannon prefab that will shoot projectiles that are a sub class of FT_Evading Projectile. 
- **My FT_Evade Projectile**, the projectile that will hit the player.

![Location of blueprints](Hints/Blueprints.png)

## Task
- Adjust the player and the projectiles collisions so if the player performs a dash they will pass throught the projectile
## Hints  

To do this task you should use [collision layers](https://dev.epicgames.com/documentation/unreal-engine/collision-in-unreal-engine---overview). By putting colliders into layer we can decide when functionality should occur, e.g. a player can ignore a certian wall collider while enemies cannot. 

## Changes from base project

The project has had some adjustments the two key are the creation of the **Auto Cannon** (Sources->Public) and the **FT_Evading Projectile** script. The cannon has a basic timer based upon the delta time that will fire a projectile every 10 seconds. The project is the same and the standardard 1st preson projectile, with some speed adjustments and disabling gravity. 



## Challenges
Test your might

## Easy 
- Expose the shoot delay so cannons can shoot at different times (See **AutoCannon.cpp** for timer)
- Add a start shoot delay to the cannons so you can have cannons, start firing at different times (See **AutoCannon.cpp** for timer)
- Add a rotation option so some spin when after shooting 
```
AddActorLocalRotation(FRotator(0.f, 90.f, 0.f));
```

## Medium
- I have done a simple timer, in reality you shout use the FTimer, see the an overview [here](https://tomlooman.com/unreal-engine-cpp-timers/) and try to replace the shoot with this technique 
- If the player hits the projectile while not dashing, move the player back to the start position (**SetActorLocation**)
- Redesign the map to expand on the use of the dash mechanic

## Hard
- Notice in the projectile we manually **bind** to a **user-made OnHit** Function:
```
// Use a sphere as a simple collision representation
CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
CollisionComp->InitSphereRadius(160.0f);
CollisionComp->BodyInstance.SetCollisionProfileName("Projectile");
CollisionComp->OnComponentHit.AddDynamic(this, &AFT_EvadeProjectile::OnHit);		// set up a notification for when this component hits something blocking
``` 
If you have done the I-Frame Collision layers properly you would have set the collision layer as well. Try to create an extra [smaller collision box](https://dev.epicgames.com/documentation/unreal-engine/API/Runtime/Engine/Components/UBoxComponent?application_version=5.5) on top of the projectile that isn't binded to that function, that will allow the player to land and jump off it, like [bullet bill in Mario](https://www.youtube.com/watch?v=Rk8kbhmaHwc&t). This is one way of doing the task, if you prefer trying other techniques feel free
- Create a moving platform for the player, you can ether move between two points (**FVector**) in code or a more complete it to create an array of actors that define a path.
- Test out other techniques use the [**Unreal Sequencer**](https://unrealcommunity.wiki/sequencer-d660d1) or expand the rotation code to objects like [swinging axes.](https://www.youtube.com/watch?v=L-OfAJRahEI) 

# Reference
Content is made by Connah Kendrick (Connah.Kendrick@mmu.ac.uk) using the Unreal Engine FPS Template for the MMU 1st year Game Mechanics Module taught to both Game Development and Game Design Students. 