//
//  Particle.cpp
//  SimpleTentacle
//
//  Created by Craig Pickard on 1/7/17.
//
//

#include "Particle.hpp"
#include "Simplex.h"

Particle::Particle(){};

Particle::~Particle(){};

Particle::Particle( ci::vec3 location )
{
    mLocation = location;
    mAcceleration = ci::vec3(0.);
    mVelocity = ci::vec3(0.0);
    mMass = 200.0;
    mLocked = false;
    mRadiusOfInfluence = 20.f;
}

void Particle::debug(){
    std::cout << "acc: " << mAcceleration << std::endl;
    std::cout << "vel: " << mVelocity << std::endl;
}

void Particle::applyForce( ci::vec3 force )
{
    force /= mMass;
    mAcceleration += force;
    
}

// Method to update location
void Particle::update()
{
//    std::cout << "particle acc(before): " << mAcceleration << std::endl;
    
    if (!mLocked){
        mVelocity += mAcceleration;
        mLocation += mVelocity;
        mAcceleration = ci::vec3(0.);
//        mVelocity *= (1.0 - mDamp);
    }

    
//    std::cout << "particle acc(after): " << mAcceleration << std::endl;
}

void Particle::addToAcceleration(ci::vec3 acc){
    mAcceleration += acc;
}

void Particle::attract(ci::vec3 loc){
    
    float dist = distance(mLocation,loc);
    float distForce = dist * 0.05;
    
    ci::vec3 dir = mLocation - loc;
    dir = normalize(dir);
    ci::vec3 force = distForce * dir;
    
//    std::cout << "dist: " << dist << std::endl;
    
    if (dist < mRadiusOfInfluence) {
        applyForce(-force);
//        std::cout << "reaching! " << std::endl;
    }
    
}

void Particle::moveRandomly()
{
    mAcceleration = Simplex::curlNoise(mLocation);
    mAcceleration /= 15000.;
    update();
}

void Particle::lock()
{
    mLocked = true;
}

// Method to display
void Particle::display()
{
    ci::gl::drawSphere(mLocation, .4);
}

void Particle::drawSphereOfInfluence(){
    
    ci::gl::ScopedColor color( ci::Color( 1., 0., 0. ) );
    ci::gl::drawSphere(mLocation, mRadiusOfInfluence);
}

