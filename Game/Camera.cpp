#include "Camera.h"


Camera::Camera() : m_phi(0), m_theta(0), m_orientation(), m_verticalAxe(0, 0, 1), m_lateralMove(), m_position(), m_targetPoint()
{
}

Camera::Camera(vec3 position, vec3 targetPoint, vec3 verticalAxe) : m_phi(-35.26), m_theta(-135), m_orientation(), m_lateralMove(), m_position(position), m_targetPoint(targetPoint), m_verticalAxe(verticalAxe)
{
}

void Camera::orientation(int xRel, int yRel)
{
	// On ajout l'angle (en n�gatif car dans le sens anti horaire)
	m_phi += -yRel * 0.5;
	m_theta += -xRel * 0.5;
	
	// Si Phi d�passe ou est en dessous de 89.0/-89.0, l'axe Y devient parral�le, c'est pas bon
	if (m_phi > 89.0)
		m_phi = 89.0;
	else if (m_phi < -89.0)
		m_phi = -89.0;

	float phiRadian = m_phi * M_PI / 180;
	float thetaRadian = m_theta * M_PI / 180;

	if (m_verticalAxe.x == 1.0)
	{
		m_orientation.x = sin(phiRadian);
		m_orientation.y = cos(phiRadian) * cos(thetaRadian);
		m_orientation.z = cos(phiRadian) * sin(thetaRadian);
	}

	else if (m_verticalAxe.y == 1.0)
	{
		m_orientation.x = cos(phiRadian) * sin(thetaRadian);
		m_orientation.y = sin(phiRadian);
		m_orientation.z = cos(phiRadian) * cos(thetaRadian);
	}
	else
	{
		m_orientation.x = cos(phiRadian) * cos(thetaRadian);
		m_orientation.y = cos(phiRadian) * sin(thetaRadian);
		m_orientation.z = sin(phiRadian);
	}

	m_lateralMove = cross(m_verticalAxe, m_orientation);
	m_lateralMove = normalize(m_lateralMove);

	m_targetPoint = m_position + m_orientation;
}

void Camera::move(Input* const &input)
{
	if (input->movedMouse())
	{
		orientation(input->getXRel(), input->getYRel());
	}

	if (input->getKey(SDL_SCANCODE_UP))
	{
		m_position = m_position + m_orientation * 0.5f;
		m_targetPoint = m_position + m_orientation;
	}

	if (input->getKey(SDL_SCANCODE_DOWN))
	{
		m_position = m_position - m_orientation * 0.5f;
		m_targetPoint = m_position + m_orientation;
	}

	if (input->getKey(SDL_SCANCODE_LEFT))
	{
		m_position = m_position + m_lateralMove * 0.5f;
		m_targetPoint = m_position + m_orientation;
	}

	if (input->getKey(SDL_SCANCODE_RIGHT))
	{
		m_position = m_position - m_lateralMove * 0.5f;
		m_targetPoint = m_position + m_orientation;
	}
}

void Camera::lookAt(mat4 &modelview)
{
	modelview = glm::lookAt(m_position, m_targetPoint, m_verticalAxe);
}

Camera::~Camera()
{
}
