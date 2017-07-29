#include "ChunkSection.h"

#include "../Block/BlockId.h"

#include "../World.h"

#include <iostream>

ChunkSection::ChunkSection(const sf::Vector3i& location, World& world)
:   m_location  (location)
,   m_pWorld    (&world)
{
    static_assert(sizeof(m_blocks) == CHUNK_VOLUME, "Size too big, yo");
    std::cout << sizeof(m_blocks) << " " << sizeof(*this) << std::endl;
}

void ChunkSection::setBlock(int x, int y, int z, ChunkBlock block)
{
    if (outOfBounds(x) ||
        outOfBounds(y) ||
        outOfBounds(z))
    {
        auto location = toWorldPosition(x, y, z);
        m_pWorld->setBlock(location.x, location.y, location.z, block);
        return;
    }

    m_blocks[getIndex(x, y, z)] = block;
}

ChunkBlock ChunkSection::getBlock(int x, int y, int z) const
{
    if (outOfBounds(x) ||
        outOfBounds(y) ||
        outOfBounds(z))
    {
        auto location = toWorldPosition(x, y, z);
        return m_pWorld->getBlock(location.x, location.y, location.z);
    }

    return m_blocks[getIndex(x, y, z)];
}

const sf::Vector3i ChunkSection::getLocation() const noexcept
{
    return m_location;
}

bool ChunkSection::hasMesh() const noexcept
{
    return m_hasMesh;
}

sf::Vector3i ChunkSection::toWorldPosition(int x, int y, int z) const
{
    return
    {
        m_location.x * CHUNK_SIZE + x,
        m_location.y * CHUNK_SIZE + y,
        m_location.z * CHUNK_SIZE + z
    };
}

bool ChunkSection::outOfBounds(int value)
{
    return  value >= CHUNK_SIZE ||
            value < 0;
}

int ChunkSection::getIndex(int x, int y, int z)
{
    return  y *
            CHUNK_AREA + z *
            CHUNK_SIZE + x;
}

