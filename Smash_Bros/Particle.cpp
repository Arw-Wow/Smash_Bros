#include "Particle.h"

Particle::Particle(const Vector2& position, Atlas* atlas, int lifespan) : position(position), atlas(atlas), lifespan(lifespan) { }

void Particle::set_atlas(Atlas* new_atlas)
{
    atlas = new_atlas;
}

void Particle::set_lifespan(int ms)
{
    lifespan = ms;
}

void Particle::set_position(int x, int y)
{
    position.x = x;
    position.y = y;
}

bool Particle::check_valid() const
{
    return is_valid;
}

void Particle::on_update(int delta)
{
    timer += delta;

    if (timer >= lifespan)
    {
        timer -= lifespan;
        index_frame++;
        if (index_frame >= atlas->getSize())
        {
            index_frame = atlas->getSize() - 1;
            is_valid = false;
        }
    }
}

void Particle::on_draw(const Camera& camera) const
{
    putimage_alpha(camera, position.x, position.y, atlas->getImage(index_frame));
}
