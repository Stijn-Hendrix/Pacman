#pragma once

namespace Pacman {

	class FpsCounter
	{
	public:

		FpsCounter(float delay = 0.1f) : m_Delay(delay)
		{

		}

		int GetFPS() const { return m_FPS; }

		void Tick(float ts)
		{
			m_TimeSinceReset += ts;

			m_FrameCount++;

			if (m_TimeSinceReset >= m_Delay)
			{
				m_FPS = m_FrameCount / m_TimeSinceReset;
				m_TimeSinceReset = 0;
				m_FrameCount = 0;
			}

		}

	private:
		float m_Delay;

		int m_FPS = 0;
		int m_FrameCount = 0;
		float m_TimeSinceReset = 0;

	};


}
